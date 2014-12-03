#ifndef MESH_H
#define MESH_H

#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

#include <vector>


class Ball;

using namespace std;

struct Vertex
{
    GLdouble x, y, z;
};

/**
  * @brief Tipo para definir la Normal de un vertice.
  */
struct Normal
{
    GLdouble nx, ny, nz;
};

/**
  * @brief Tipo para definir la coordenada de textura de un vertice.
  */
struct TexCoord
{
    GLdouble u, v;
};

/**
  * @brief Tipo para definir un triangulo.
  */
struct Triangle
{
    GLint vertex[3];
    Normal normal;
};


class Mesh
{
    vector<Vertex> _vertices;
    vector<Triangle> _triangles;
    vector<Normal> _normals;
    vector<TexCoord> _texCoords;

    Vertex _position;


public:

    Mesh();


    void draw();

    int collide(Ball* ball, vector<Triangle> &collidedTriangles);

    void addVertex(double x, double y, double z);
    void addNormal(double nx, double ny, double nz);
    void addTexCoord(double u, double v);
    void addTriangle(int v1, int v2, int v3);

    int getNumVertices() {return _vertices.size();}
    int getNumTriangles() {return _triangles.size();}
    int getNumTexCoords() {return _texCoords.size();}
    int getNumNormals() {return _normals.size();}

    Vertex getVertex(int pos) {return _vertices[pos];}
    vector<Triangle> getTriangles() {return _triangles;}
    Vertex getPosition() {return _position;}
    void setPosition(double x, double y, double z) {_position.x = x; _position.y = y; _position.z = z;}
};




#endif // MESH_H
