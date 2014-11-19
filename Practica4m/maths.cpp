#include "maths.h"

#include <math.h>

//Devuelve el vector resultado de restar los dos vectores
Normal Maths::subtract(Vertex v1, Vertex v2)
{
    Normal sol;
    sol.nx = v1.x - v2.x;
    sol.ny = v1.y - v2.y;
    sol.nz = v1.z - v2.z;
    return sol;
}

//Devuelve el producto vectorial de los dos vectores
Normal Maths::crossProduct(Normal n1, Normal n2)
{
    Normal sol;
    sol.nx = n1.ny * n2.nz - n1.nz * n2.ny;
    sol.ny = -(n1.nx * n2.nz - n1.nz * n2.nx);
    sol.nz = n1.nx * n2.ny - n1.ny * n2.nx;
    return sol;
}

//Devuelve el módulo del vector
GLdouble Maths::module(Normal n){
    return (GLdouble) sqrt(n.nx * n.nx + n.ny * n.ny + n.nz * n.nz);
}

//Devuelve el vector normalizado
Normal Maths::normalize(Normal n){
    Normal sol;
    GLdouble mod = module(n);
    sol.nx = n.nx / mod;
    sol.ny = n.ny / mod;
    sol.nz = n.nz / mod;
    return sol;
}



