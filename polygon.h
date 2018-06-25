#ifndef POLYGON_H
#define POLYGON_H

#if defined (__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <list>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <glm/mat4x4.hpp> // glm::mat4
#include "vertex.h"

using namespace std;

extern int grid_width;
extern int grid_height;

class Polygon {
public:
    //int id;
    //int num_of_vertex;
    //int num_of_edges;
    //Vertex centroid;
    // int nCtrlPts;
    int curve;
    int degree;
    bool k;                // spline
    vector <float> knots;       // spline
    vector <Vertex> splPoints;  // spline
    vector <float> knotVector; //spline

    int nBezCurvePts;    // bezier
    vector <Vertex> vertices;   // bezier
    vector <Vertex> bezPoints;  // bezier
    
    
    vector <int> temp;
    //vector <Connection> connections;

    Polygon();
    
    void binomialCoeffs (GLint n, GLint * C);
    void computeBezPt(GLfloat u, Vertex *bezPt, GLint *C, int size);
    void bezier ();
    void changeDegree (int val);
    void initKnots();
    void updateCurve();
    float calculateWeightForPointI( int i, int k, int cps, float t );
    float knot(int indexForKnot);
    void createKnotVector(int curveOrderK, int numControlPoints);

    // void plotPoint (Vertex bezCurvePt) {
    //     glBegin (GL_POINTS);
    //         glVertex2f (bezCurvePt.x, bezCurvePt.y);
    //     glEnd ( ); 
    // }

   
    // void setCentroid();
    // void setId(int id);
    // void setNum(int num);
    // void setEdge(int num);

    // void cavMatrix(float matrix[4][4]);
    // void newPosition(float temp[4][1], float x, float y, float z);
    // void matrixMul(float matrix[4][4], float newP[4][1]);
    // void cav();

    // void printMatrix(float matrix[4][4]);
    // void printCentroid();

    // void cab();
    // void cabMatrix(float matrix[4][4]);

    // void transMatrix(float matrix[4][4], float x, float y, float z);
    // void transl(float x, float y, float z);

    // void scaleMatrix(float matrix[4][4], float tx);
    // void scale(float tx);
    // void complexScale(float tx);

    // void xyMatrix(float matrix[4][4]);
    // void xyProjection();

    // void xzMatrix(float matrix[4][4]);
    // void xzProjection();

    // void yzMatrix(float matrix[4][4]);
    // void yzProjection();

    // void xRotateMatrix(float matrix[4][4], float degree);
    // void xRotate(float degree);

    // void yRotateMatrix(float matrix[4][4], float degree);
    // void yRotate(float degree);

    // void zRotateMatrix(float matrix[4][4], float degree);
    // void zRotate(float degree);

    // void complexRotation(float degree, float x0, float y0, float z0, float x1, float y1, float z1);
}; //class polygon

#endif