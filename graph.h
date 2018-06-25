#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include "polygon.h"
#include "vertex.h"
using namespace std;

extern int grid_width;
extern int grid_height;

class Graph {
public:
    vector <Polygon> polys;
    int xMax, xMin, yMax, yMin, zMax, zMin;

    Graph();
    void initialization ();
    void printInfo(int i);
    void setXYZ();
    // void equal(Graph temp);
    // void equalOne(Graph temp, int num);
}; //graph class

#endif