#ifndef MATHS_H
#define MATHS_H

#include "mesh.h"

class Maths
{
public:

     static Normal subtract(Vertex v1, Vertex v2);
     static Normal crossProduct(Normal n1, Normal n2);
     static GLdouble module(Normal n);
     static Normal normalize(Normal n);

};

#endif // MATHS_H
