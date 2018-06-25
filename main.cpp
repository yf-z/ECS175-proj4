/*
* Simple glut demo that can be used as a template for
* other projects by Garrett Aldrich
*/


#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//other includes
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include "vertex.h"
#include "polygon.h"
#include "graph.h"


/****set in main()****/
//the number of pixels in the grid
int grid_width;
int grid_height;
Graph origin;
bool mouseinput = false;
bool mousedelete = false;
bool mouseadd = false;
bool mousechange = false;
bool isBezier = true;
int pindex = -1;
int id = -1;
int aid = -1;
int pid = -1;
float kid = -1;
float kindex = -1;


//the size of pixels sets the inital window height and width
//don't make the pixels too large or the screen size will be larger than
//your display size
float pixel_size;

/*Window information*/
int win_height;
int win_width;


void init();
void idle();
void display();
void draw_lines(Graph frame, bool isline);
void draw_pix(float x, float y);
void draw_lines3D(Graph frame);
void reshape(int width, int height);
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void check();



int main(int argc, char **argv)
{
   
   //the number of pixels in the grid
   grid_width = 800;
   grid_height = 800;
   
   //the size of pixels sets the inital window height and width
   //don't make the pixels too large or the screen size will be larger than
   //your display size
   pixel_size = 1;
   
   /*Window information*/
   win_height = grid_height;//*pixel_size;
   win_width = grid_width;//*pixel_size;
   
   /*Set up glut functions*/
   /** See https://www.opengl.org/resources/libraries/glut/spec3/spec3.html ***/
   
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   /*initialize variables, allocate memory, create buffers, etc. */
   //create window of size (win_width x win_height
   glutInitWindowSize(win_width,win_height);
   //windown title is "glut demo"
   glutCreateWindow("glut demo");
   
   /*defined glut callback functions*/
   glutDisplayFunc(display); //rendering calls here
   glutReshapeFunc(reshape); //update GL on window size change
   glutMouseFunc(mouse);     //mouse button events
   glutMotionFunc(motion);   //mouse movement events
   glutKeyboardFunc(key);    //Keyboard events
   glutIdleFunc(idle);       //Function called while program is sitting "idle"
   
   //initialize opengl variables
   //filename = argv[1];
   init();
   //start glut event loop
   glutMainLoop();
   return 0;
}

/*initialize gl stufff*/
void init()
{
   //set clear color (Default background to white)
   glClearColor(0,0,0,0);

    origin.initialization();
    //origin.printInfo(1);

   cout << "The default display mode is Bezier Curve\n";
   cout << "If you want to change the curve method,\n";
   cout << "please press B on the graph window and follow the instructions:)\n" << endl;

   check();
}

//called repeatedly when glut isn't doing anything else
void idle()
{
   //redraw the scene over and over again
   glutPostRedisplay();	
}

void draw_pix(float x, float y){
    glBegin(GL_POINTS);
    glColor3f(1.0,0,0);
    glVertex3f(x,y,0);
    glEnd();
}

//this is where we render the screen
void display()
{
   //clears the screen
   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

    if (origin.polys.size() != 0) {
        draw_lines(origin, false);

        for (int i = 0; i < origin.polys.size(); i++) {
            for (int j = 0; j < origin.polys[i].vertices.size(); j++) {
                glPointSize(5);                    
                draw_pix(origin.polys[i].vertices[j].x , origin.polys[i].vertices[j].y);
            }
            if (isBezier) {
                if (origin.polys[i].vertices.size() > 1) {
                    origin.polys[i].bezPoints.clear();
                    origin.polys[i].bezier();
                }
                if (origin.polys[i].vertices.size() > 1)
                     draw_lines(origin, true);
            } else {
                origin.polys[i].updateCurve();
                if (origin.polys[i].vertices.size() > 1)
                    draw_lines(origin, true);
            }
        }
    }
   
   //blits the current opengl framebuffer on the screen
   glutSwapBuffers();
   //checks for opengl errors
   check();
}


void draw_lines(Graph frame, bool isline){
   glLineWidth(2.0); //sets the "width" of each line we are rendering
   //tells opengl to interperate every two calls to glVertex as a line
   glBegin(GL_LINES);
   //first line will be blue

    if (!isline) {
        for (int i = 0; i < frame.polys.size(); i++) {
            if (frame.polys[i].vertices.size() > 1) {
                for (int j = 0; j < frame.polys[i].vertices.size() - 1; j++) {
                glColor3f(0, 0, 1);
                glVertex2f(frame.polys[i].vertices[j].x, frame.polys[i].vertices[j].y);
                glVertex2f(frame.polys[i].vertices[j+1].x, frame.polys[i].vertices[j+1].y);
                }  
            }
        }   
    }
    else {
        
            for (int i = 0; i < frame.polys.size(); i++) {
                if (!isBezier && frame.polys[i].splPoints.size() != 0) {
                if (frame.polys[i].vertices.size() > 2) {
                for (int j = 0; j < frame.polys[i].splPoints.size() - 1; j++) {
                    glColor3f(1, 0, 0);
                    glVertex2f(frame.polys[i].splPoints[j].x, frame.polys[i].splPoints[j].y);
                    glVertex2f(frame.polys[i].splPoints[j+1].x, frame.polys[i].splPoints[j+1].y);
                }
                }  
            } 
        }

            for (int i = 0; i < frame.polys.size(); i++) {
                if (isBezier && frame.polys[i].bezPoints.size() != 0) {
                if (frame.polys[i].vertices.size() > 2) {
                for (int j = 0; j < frame.polys[i].bezPoints.size() - 1; j++) {
                    glColor3f(1, 0, 0);
                    glVertex2f(frame.polys[i].bezPoints[j].x, frame.polys[i].bezPoints[j].y);
                    glVertex2f(frame.polys[i].bezPoints[j+1].x, frame.polys[i].bezPoints[j+1].y);
                }  
                }
            } 
        }
    }
//    glColor3f(0,0,1.0);
//    glVertex2f(0.1,0.1);
//    glVertex2f(.9,.9);

   //this will be a red line
   //notice we can use 3d points too
   //how will this change if we project to the XZ or YZ plane?
//    glColor3f(1.0,0.0,0.0);
//    glVertex3f(0.1,0.9,0.5);
//    glVertex3f(0.9,0.1,0.3);
   glEnd();
}

/*Gets called when display size changes, including initial craetion of the display*/
/*this needs to be fixed so that the aspect ratio of the screen is consistant with the orthographic projection*/

void reshape(int width, int height)
{
	/*set up projection matrix to define the view port*/
    //update the ne window width and height
	win_width = width;
	win_height = height;
    
    //creates a rendering area across the window
	glViewport(0,0,width,height);
    // up an orthogonal projection matrix so that
    // the pixel space is mapped to the grid space
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//glOrtho(origin.xMin,origin.xMax,origin.yMin,origin.yMax,-1,1);
    gluOrtho2D(0, grid_width , 0, grid_height);
    //glOrtho(0, grid_width , 0, grid_height, 0, 0);
    
    //clear the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //set pixel size based on width, if the aspect ratio
    //changes this hack won't work as well
    //pixel_size = width/(float)grid_width;
    
    //set pixel size relative to the grid cell size
    glPointSize(pixel_size);
    //check for opengl errors
	check();
}

//gets called when a key is pressed on the keyboard
void key(unsigned char ch, int x, int y)
{
    Polygon poly;
       Vertex temp;
       int cur;
       ofstream fout;
       fout.open("output.txt");
   switch(ch)
   {
      case 'u':
        mouseinput = false;
        mouseadd = false;
        mousechange = false;
        mousedelete = false;
        cout << "please enter new sub curve number:" << endl;
        cin >> cur;
        if (cur > 1 && cur < 5) {
            for (int i = 0; i < origin.polys.size(); i++) {
                origin.polys[i].curve = cur;
            }
        }
        else cout << "wrong curve number!!! :(" << endl;
        break;
       case 'b' :
            isBezier = !isBezier;
            break;
       case 'i' :
        mouseinput = !mouseinput;
        mouseadd = false;
        mousechange = false;
        mousedelete = false;
        if (mouseinput) {   
            cout << "please enter the new curve id" << endl;
            cin >> id;
        }
        else id = -1;
        break;
        case 'd' :
            mousedelete = !mousedelete;
            mouseadd = false;
            mousechange = false;
            mouseinput = false;
            break;
        case 'a' :
            mouseadd = !mouseadd;
            mouseinput = false;
            mousechange = false;
            mousedelete = false;
            if (mouseadd) {   
                cout << "please enter the curve id that you wang to add points" << endl;
                cin >> aid;
            }
            else aid = -1;
            if (aid > origin.polys.size())
            {
              cout << "curve id does not exist or add mode is turned off! :(" << endl;
            }
            break;
        case 'p' :
            mousechange = !mousechange;
            pindex = -1;
            mouseinput = false;
            mouseadd = false;
            mousedelete = false;
            break;
        case 'c' :
            for (int i = 0; i < origin.polys.size(); i++) {
                origin.polys[i].vertices.clear();
            }
            origin.polys.clear();
            
            temp.x = -300;
            temp.y = -300;
            //vector <Vertex> v;
            //v.push_back(temp);
            
            poly.vertices.push_back(temp);
            origin.polys.push_back(poly);
            //origin.printInfo(1);
            break;
         case 'q' :
         cout << "Thanks for your using :)" <<  endl;
         if (origin.polys.size() == 1 && origin.polys[0].vertices[0].x == -300) {
          fout << "No curve in this graph" << endl;
         }
         else {
           fout << "the number of the curve is: " << origin.polys.size() << endl << endl;
           for (int i = 0; i < origin.polys.size(); i++) {
            fout << "the id of the curve is: " << i+1 << endl << endl;
            fout << "the vertex of the curve is: " << endl;
            for (int j = 0; j < origin.polys[i].vertices.size(); j++) {
              fout << "(" << origin.polys[i].vertices[j].x << "," << origin.polys[i].vertices[j].y << ")" << " --> ";
            }
            fout << "end" << endl << endl << endl;
           }
         }
         exit(0);
         break; 
       default:
           //prints out which key the user hit
           printf("User hit the \"%c\" key\n",ch);
           break;
   }
   //redraw the scene after keyboard input
   glutPostRedisplay();
}

//gets called when the curser moves accross the scene
void motion(int x, int y)
{
   //redraw the scene after mouse movement
   glutPostRedisplay();
}

//checks for any opengl errors in the previous calls and
//outputs if they are present
void check()
{
   GLenum err = glGetError();
   if(err != GL_NO_ERROR)
   {
       printf("GLERROR: There was an error %s\n",gluErrorString(err) );
       exit(1);
   }
}

void mouse(int button, int state, int x, int y)
{
    //print the pixel location, and the grid location
    // for (int i = 0; i < origin.polys[0].splPoints.size(); i++) {
    //     cout << origin.polys[0].splPoints[i].x << ' ' << origin.polys[0].splPoints[i].y << endl;
    // }
    // cout << "Knot size : " << origin.polys[0].knotVector.size() << endl;
    // cout << "--------------------------" << endl;
    //printf ("MOUSE AT PIXEL: %d %d, GRID: %d %d\n",x,y,(int)(x/pixel_size),(int)((win_height-y)/pixel_size));
    int newx = (int)(x);
    int newy = (int)((win_height-y));
    int tid;
	// switch(button)
	// {
	// 	case GLUT_LEFT_BUTTON: //left button
    //         printf("LEFT ");
    //         break;
	// 	case GLUT_RIGHT_BUTTON: //right button
    //         printf("RIGHT ");
	// 	default:
    //         printf("UNKNOWN "); //any other mouse button
	// 		break;
	// }
    // if(state !=GLUT_DOWN)  //button released
    //     printf("BUTTON UP\n");
    // else
    //     printf("BUTTON DOWN\n");  //button clicked
    
    if (mouseinput && id > 0){
        Vertex vertex;
        vertex.x = newx;
        vertex.y = newy;
        if (id == 1) {
            int l = origin.polys[0].vertices.size();
            if (origin.polys[0].vertices[0].x != -300) {
            if (!((newx >= origin.polys[0].vertices[l-1].x-5 && newx <= origin.polys[0].vertices[l-1].x+5) && (newy >= origin.polys[0].vertices[l-1].y-5 && newy <= origin.polys[0].vertices[l-1].y+5))) {
                origin.polys[0].vertices.push_back(vertex);
                }
            }
                else {
                    origin.polys[0].vertices[0].x = newx;
                    origin.polys[0].vertices[0].y = newy;
                }
        }
        else if (id > 1) {
            if (id > origin.polys.size()) {
                
                Vertex v;
                Polygon poly;
                v.x = newx;
                v.y = newy;
                poly.vertices.push_back(v);
                origin.polys.push_back(poly);
            }
            else {
                Vertex v;
                v.x = newx;
                v.y = newy;
                int l = origin.polys[id-1].vertices.size();
                if (!((newx >= origin.polys[id-1].vertices[l-1].x-5 && newx <= origin.polys[id-1].vertices[l-1].x+5) && (newy >= origin.polys[id-1].vertices[l-1].y-5 && newy <= origin.polys[id-1].vertices[l-1].y+5))) {
                    origin.polys[id-1].vertices.push_back(v);
                }
            }
        }
    }

    if (mousedelete) {
        for (int j = 0; j < origin.polys.size(); j++) {
            for (int i = 0; i < origin.polys[j].vertices.size(); i++) {
                if ((newx >= origin.polys[j].vertices[i].x-5 && newx <= origin.polys[j].vertices[i].x+5) && (newy >= origin.polys[j].vertices[i].y-5 && newy <= origin.polys[j].vertices[i].y+5)) {
                    if (origin.polys[j].vertices.size() != 1)
                        origin.polys[j].vertices.erase(origin.polys[j].vertices.begin() + i);
                        else cout << "only one vertex left, please use clean to delete it" << endl;
                }
            }
        }
    }

    if (mouseadd && aid > 0) {
        bool exist = false;
        for (int i = 0; i < origin.polys[aid-1].vertices.size(); i++) {
            if ((newx >= origin.polys[aid-1].vertices[i].x-5 && newx <= origin.polys[aid-1].vertices[i].x+5) && (newy >= origin.polys[aid-1].vertices[i].y-5 && newy <= origin.polys[aid-1].vertices[i].y+5))
                exist = true;
        }

        if (exist) {
            //cout << "Sorry the point is already existed :(" << endl;
        }
        else {
            Vertex vertex;
            vertex.x = newx;
            vertex.y = newy;
            origin.polys[aid-1].vertices.push_back(vertex);
        }
    }

    if (mousechange && pindex >= 0) {
        origin.polys[pid].vertices[pindex].x = newx;
        origin.polys[pid].vertices[pindex].y = newy;
        //pindex = -1;
    }

    if (mousechange && pindex < 0) {
        for (int j = 0; j < origin.polys.size(); j++) {
            for (int i = 0; i < origin.polys[j].vertices.size(); i++) {
                if ((newx >= origin.polys[j].vertices[i].x-5 && newx <= origin.polys[j].vertices[i].x+5) && (newy >= origin.polys[j].vertices[i].y-5 && newy <= origin.polys[j].vertices[i].y+5)) {
                    pindex = i;
                    pid = j;
                }
            }
        }
    }

    //origin.setXYZ();
    //origin.printInfo(1);
    //     if (mouseinput)
    //         cout << "mouseinput is true" << endl;
    //         else cout << "mouseinput is false" << endl;
    //     if (mousedelete)
    //         cout << "mousedelete is true" << endl;
    //         else cout << "mousedelete is false" << endl;
    //             if (mousechange)
    //         cout << "mousechange is true" << endl;
    //         else cout << "mousechange is false" << endl;
    //         cout << "index: " << pindex << endl;
    //         cout << pid <<  " --- " << pindex << endl;
    // cout << "===========================================" << endl;
    //redraw the scene after mouse click
    glutPostRedisplay();
}