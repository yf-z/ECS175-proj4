#include "vertex.h"
#include "polygon.h"

Polygon::Polygon() {
    curve = 3;
    degree = 3;
    nBezCurvePts = 100;
    k = false;
}

 void Polygon::binomialCoeffs (GLint n, GLint * C) {
        bool equal = false;
        bool jequal = false;
        int e; 
        GLint k, j;
        for (k = 0; k <= n; k++) { 
            // Compute n!/(k!(n - k)!)
            C [k] = 1; 
            for (j = n; j >= k + 1; j--) {
                if (j >= 2 && j <= n-k) {
                    equal = true;
                }
                if (equal == false) {
                    C [k] *= j;
                }
                else {equal = false;}
            }
             for (j = n - k; j >= 2; j--) {
                if (j >= k+1 && j <= n) {
                     jequal = true;
                }
                 if (jequal == false) {
                    C [k] /= j;
                 }
                 else {jequal = false;}
             }
        }
    }

    void Polygon::computeBezPt(GLfloat u, Vertex *bezPt, GLint *C, int size) {
        int nCtrlPts = size;
        GLint k, n = nCtrlPts - 1;
        GLfloat bezBlendFcn;
        bezPt->x = 0.0;
        bezPt->y = 0.0;


        for (k = 0; k < nCtrlPts; k++) {
            bezBlendFcn = C [k] * pow (u, k) * pow (1 - u, n - k);
            bezPt->x += vertices [k].x * bezBlendFcn; 
            bezPt->y += vertices [k].y * bezBlendFcn; 
        }
    }

    void Polygon::bezier () {
        temp.clear();
        Vertex bezCurvePt; 
        GLfloat u; 
        GLint *C, k;
        
        int nCtrlPts = vertices.size();

        // Allocate space for binomial coefficients 
        C = new GLint [nCtrlPts+1];

        binomialCoeffs(nCtrlPts - 1, C);

        for (k = 0; k <= nBezCurvePts; k++) {
            u = GLfloat (k) / GLfloat (nBezCurvePts);
            computeBezPt (u, &bezCurvePt, C, nCtrlPts);
            // plotPoint (bezCurvePt);
            bezPoints.push_back(bezCurvePt);
        }

        // for (int i = 0; i < nCtrlPts; i++) {
        //     cout << C[i] << ' ';
        // }
        // cout << endl;

        delete[] C;
    }

    void Polygon::changeDegree (int val) {
        degree = val;
    }

    void Polygon::initKnots() {
        for(int i = 0; i < degree; i++)
		    knots.push_back(0);

        int nSegment = vertices.size() - degree;
        
        if(nSegment == 0) {
            knots.push_back(0);            
        } else {
            for(int i=0; i <= nSegment; i++)
                knots.push_back(((float) i)/nSegment);
        }

        for(int i=0; i < degree; i++)
            knots.push_back(1);
    }

void Polygon::updateCurve()
{
    int subCurveOrder = curve; // = k = I want to break my curve into to cubics

    // De boor 1st attempt
    if(vertices.size() >= subCurveOrder)
    {
        knotVector.clear();
        createKnotVector(subCurveOrder, vertices.size());
        splPoints.clear(); 

        for(int steps=0; steps<=1000; steps++)
        {
            // use steps to get a 0-1 range value for progression along the curve
                    // then get that value into the range [k-1, n+1]
            // k-1 = subCurveOrder-1
            // n+1 = always the number of total control points

            float t = ( steps / 1000.0f ) * ( vertices.size() - (subCurveOrder-1) ) + subCurveOrder-1;

            Vertex temp;
            temp.x = temp.y = temp.z = 0;
            for(int i=1; i <= vertices.size(); i++)
            {
                float weightForControl = calculateWeightForPointI(i, subCurveOrder, vertices.size(), t);
                temp.x += weightForControl * vertices[i-1].x;
                temp.y += weightForControl * vertices[i-1].y;
                temp.z += weightForControl * vertices[i-1].z;
            }
            splPoints.push_back(temp);
        }
    }
        //     kid = -1;
        // kindex = -1;
}

    //i = the weight we're looking for, i should go from 1 to n+1, where n+1 is equal to the total number of control points.
    //k = curve order = power/degree +1. eg, to break whole curve into cubics use a curve order of 4
    //cps = number of total control points 
    //t = current step/interp value
float Polygon::calculateWeightForPointI( int i, int k, int cps, float t )
{
        //test if we've reached the bottom of the recursive call
        if( k == 1 )
        {
            if( t >= knot(i) && t < knot(i+1) )
                return 1;
            else
                return 0;
        } 

        float numeratorA = ( t - knot(i) );
        float denominatorA = ( knot(i + k-1) - knot(i) );
        float numeratorB = ( knot(i + k) - t );
        float denominatorB = ( knot(i + k) - knot(i + 1) );

        float subweightA = 0;
        float subweightB = 0;

        if( denominatorA != 0 )
            subweightA = numeratorA / denominatorA * calculateWeightForPointI(i, k-1, cps, t);
        if( denominatorB != 0 )
            subweightB = numeratorB / denominatorB * calculateWeightForPointI(i+1, k-1, cps, t);

        return subweightA + subweightB;

}

    //returns the knot value at the passed in index 
    //if i = 1 and we want Xi then we have to remember to index with i-1
float Polygon::knot(int indexForKnot)
{
         // When getting the index for the knot function i remember to subtract 1 from i because of the difference caused by us counting from i=1 to n+1 and indexing a vector from 0
         return knotVector.at(indexForKnot-1);
}
    //calculate the whole knot vector
void Polygon::createKnotVector(int curveOrderK, int numControlPoints)
{
        int knotSize = curveOrderK + numControlPoints;
        for(int count = 0; count <= knotSize; count++)
        {
                knotVector.push_back( count );
        }
} 