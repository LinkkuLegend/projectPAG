#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>
#include "octree.h"
#include "boundingbox.h"
#include "ball.h"


using namespace std;

#define BOX_SIZE 1

class Viewer : public QGLViewer
{
    Mesh* _mesh;
    Octree* _octree;
    BoundingBox* _boundingBox;

    Ball _ball;
    int type;

    vector<Triangle> _collidedTriangles;

    void drawBox();
    void drawSphere();
    void animateBall();


protected :
    virtual void draw();
    virtual void init();
    virtual void animate();

public:
    Viewer();

    void loadModel(char* path);
    int getType() const;
    void setType(int value);
};

#endif // VIEWER_H
