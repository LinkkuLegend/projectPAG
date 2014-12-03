#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H



#include "mesh.h"
#include "ball.h"


class BoundingBox
{
    double _minX;
    double _maxX;
    double _minY;
    double _maxY;
    double _minZ;
    double _maxZ;
public:
    BoundingBox(Mesh* mesh);
    void draw();

    Vertex getCenter();
    vector<double> getHalfSize();

    int collide(Ball* ball);
};

#endif // BOUNDINGBOX_H
