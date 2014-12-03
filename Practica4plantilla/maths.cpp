#include "maths.h"

#include <math.h>


Normal Maths::subtract(Vertex v1, Vertex v2)
{
    Normal n;

    n.nx = v1.x - v2.x;
    n.ny = v1.y - v2.y;
    n.nz = v1.z - v2.z;

    return n;
}

Normal Maths::crossProduct(Normal n1, Normal n2)
{
    Normal n;

    n.nx = (n1.ny * n2.nz) - (n1.nz * n2.ny);
    n.ny = -((n1.nx * n2.nz) - (n1.nz * n2.nx));
    n.nz = (n1.nx * n2.ny) - (n1.ny * n2.nx);

    return n;
}

GLdouble Maths::module(Normal n)
{
    return sqrt(n.nx*n.nx + n.ny*n.ny + n.nz*n.nz);
}

Normal Maths::normalize(Normal n)
{
    Normal normalizedNormal;

    normalizedNormal.nx = n.nx / module(n);
    normalizedNormal.ny = n.ny / module(n);
    normalizedNormal.nz = n.nz / module(n);

    return normalizedNormal;
}



