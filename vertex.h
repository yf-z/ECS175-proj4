#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <list>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

extern int grid_width;
extern int grid_height;

class Vertex{
public:
    float x; //x-axis vector
    float y; //y-axis vector
    float z; //z-axis vector
    Vertex();
    Vertex(float x, float y, float z);
    Vertex operator=(const Vertex pt) ;
    Vertex operator+(const Vertex pt) const;
    //  Vertex operator-(const  Vertex pt) const;
    Vertex operator*(float m) const;
    Vertex operator/(float m) const;
}; //class Vertex

class Connection{
public:
    int x;
    int y;

    Connection();
    Connection(int x, int y);
}; //class connection

#endif