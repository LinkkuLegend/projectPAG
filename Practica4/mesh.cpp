#include "mesh.h"
#include <iostream>


#include "ball.h"
#include "maths.h"

Mesh::Mesh()
{
    _position.x = 0.0; _position.y = 0.0; _position.z = 0.0;
}



void Mesh::draw()
{
    glBegin(GL_TRIANGLES);
        for(unsigned i=0; i<_triangles.size(); i++)
        {
            glNormal3f(_triangles[i].normal.nx, _triangles[i].normal.ny, _triangles[i].normal.nz);
            glVertex3f(_vertices[_triangles[i].vertex[0]].x, _vertices[_triangles[i].vertex[0]].y, _vertices[_triangles[i].vertex[0]].z);
            glVertex3f(_vertices[_triangles[i].vertex[1]].x, _vertices[_triangles[i].vertex[1]].y, _vertices[_triangles[i].vertex[1]].z);
            glVertex3f(_vertices[_triangles[i].vertex[2]].x, _vertices[_triangles[i].vertex[2]].y, _vertices[_triangles[i].vertex[2]].z);
        }
    glEnd();
}

int Mesh::collide(Ball *ball, vector<Triangle> &collidedTriangles)
{
    // Detectar la colision entre la malla y la bola, y calcular los triangulos que colisionan y almacenarlos en collidedTriangles. Devuelve 1 si colisiona, 0 en caso contrario.
    Triangle aux;
    int collision = 0;
    for (int i=0;i<_triangles.size();i++)
    {
        aux = _triangles[i];
        if (ball->isInside(_vertices[aux.vertex[0]]) ||
            ball->isInside(_vertices[aux.vertex[1]]) ||
            ball->isInside(_vertices[aux.vertex[2]]))
        {
            collidedTriangles.push_back(aux);
            collision = 1;
        }
    }

    return collision;
}

void Mesh::addVertex(double x, double y, double z)
{
    Vertex p;

    p.x = x;
    p.y = y;
    p.z = z;

    _vertices.push_back(p);
}

void Mesh::addNormal(double nx, double ny, double nz)
{
    Normal n;

    n.nx = nx;
    n.ny = ny;
    n.nz = nz;

    _normals.push_back(n);
}

void Mesh::addTexCoord(double u, double v)
{
    TexCoord tc;

    tc.u = u;
    tc.v = v;

    _texCoords.push_back(tc);
}

void Mesh::addTriangle(int v0, int v1, int v2)
{
    Triangle t;

    t.vertex[0] = v0;
    t.vertex[1] = v1;
    t.vertex[2] = v2;

    Normal auxn1 =  Maths::subtract(_vertices[v1], _vertices[v0]);
    Normal auxn2 =  Maths::subtract(_vertices[v2], _vertices[v0]);
    t.normal = Maths::normalize( Maths::crossProduct(auxn1, auxn2));

    _triangles.push_back(t);
}


