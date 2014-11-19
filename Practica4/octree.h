#ifndef OCTREE_H
#define OCTREE_H

#include "mesh.h"


class Octree
{
    Mesh* _mesh;
    Octree *_children;
    vector<Triangle> _trianglesIncluded;

    Vertex _center;
    double _halfX;
    double _halfY;
    double _halfZ;

public:
    Octree();
    void generate(Mesh* mesh, int level, int minTriangles,const vector<Triangle> &triangles, Vertex center,const vector<double> &size);
    void draw();

    int collide(Ball* ball, vector<Triangle> &collidedTriangles);
    int isInside(Ball* ball);
    int isInside(Triangle t);
};

#endif // OCTREE_H
