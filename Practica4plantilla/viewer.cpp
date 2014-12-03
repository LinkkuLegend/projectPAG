#include "viewer.h"
#include "meshloader.h"



Viewer::Viewer()
{
    _mesh = NULL;
    _boundingBox = NULL;
    _octree = NULL;
}

void Viewer::loadModel(char *path)
{
    MeshLoader loader;
    loader.loadOBJ(path);

    if (_mesh != NULL)
        delete _mesh;

    _mesh = loader.getMesh();

    if (_boundingBox != NULL)
        delete _boundingBox;

    _boundingBox = new BoundingBox(_mesh);

    if (_octree != NULL)
        delete _octree;

    _octree = new Octree();
    _octree->generate(_mesh, 4, 10, _mesh->getTriangles(), _boundingBox->getCenter(), _boundingBox->getHalfSize());

    updateGL();
}



void Viewer::animate()
{
    _ball.animate();

    //Calcular colision bola-caja exterior

    float* ballPos = _ball.getPosition();
    float radius = _ball.getRadius();
    if (ballPos[0] + radius > BOX_SIZE || ballPos[0] - radius < -BOX_SIZE)
        _ball.changeDirectionX();

    if (ballPos[1] + radius > BOX_SIZE || ballPos[1] - radius < -BOX_SIZE)
        _ball.changeDirectionY();

    if (ballPos[2] + radius > BOX_SIZE || ballPos[2] - radius < -BOX_SIZE)
        _ball.changeDirectionZ();

    // Calcular colision mallas - bola


    _collidedTriangles.clear();
    if (_boundingBox)
    {
        if (_boundingBox->collide(&_ball))
        {
            if(_octree)
               _octree->collide(&_ball, _collidedTriangles);
        }

    }


}

void Viewer::draw()
{
    if (_collidedTriangles.empty())
        _ball.draw();
    else
        drawCollidedTriangles();

    drawBox();




    glColor3f(1.0, 1.0, 1.0);
    if (_mesh)
        _mesh->draw();

    //if (_boundingBox)
    //    _boundingBox->draw();

    //if (_octree)
    //    _octree->draw();


}


void Viewer::init()
{
    startAnimation();
}



void Viewer::drawCollidedTriangles()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        for (int i=0; i<_collidedTriangles.size(); i++)
        {
            glNormal3f(_collidedTriangles[i].normal.nx, _collidedTriangles[i].normal.ny, _collidedTriangles[i].normal.nz);
            glVertex3f(_mesh->getVertex(_collidedTriangles[i].vertex[0]).x, _mesh->getVertex(_collidedTriangles[i].vertex[0]).y, _mesh->getVertex(_collidedTriangles[i].vertex[0]).z);
            glVertex3f(_mesh->getVertex(_collidedTriangles[i].vertex[1]).x, _mesh->getVertex(_collidedTriangles[i].vertex[1]).y, _mesh->getVertex(_collidedTriangles[i].vertex[1]).z);
            glVertex3f(_mesh->getVertex(_collidedTriangles[i].vertex[2]).x, _mesh->getVertex(_collidedTriangles[i].vertex[2]).y, _mesh->getVertex(_collidedTriangles[i].vertex[2]).z);


        }
    glEnd();
}



void Viewer::drawBox()
{
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);

    //LEFT
    glBegin(GL_LINE_LOOP);
        glVertex3f(-BOX_SIZE, -BOX_SIZE, -BOX_SIZE);
        glVertex3f(-BOX_SIZE, BOX_SIZE, -BOX_SIZE);
        glVertex3f(-BOX_SIZE, BOX_SIZE, BOX_SIZE);
        glVertex3f(-BOX_SIZE, -BOX_SIZE, BOX_SIZE);
    glEnd();

    //TOP
    glBegin(GL_LINE_LOOP);
        glVertex3f(BOX_SIZE, BOX_SIZE, BOX_SIZE);
        glVertex3f(BOX_SIZE, BOX_SIZE, -BOX_SIZE);
        glVertex3f(-BOX_SIZE, BOX_SIZE, -BOX_SIZE);
        glVertex3f(-BOX_SIZE, BOX_SIZE, BOX_SIZE);
    glEnd();

    //RIGTH
    glBegin(GL_LINE_LOOP);
        glVertex3f(BOX_SIZE, -BOX_SIZE, BOX_SIZE);
        glVertex3f(BOX_SIZE, BOX_SIZE, BOX_SIZE);
        glVertex3f(BOX_SIZE, BOX_SIZE, -BOX_SIZE);
        glVertex3f(BOX_SIZE, -BOX_SIZE, -BOX_SIZE);
    glEnd();

    //BOTTOM
    glBegin(GL_LINE_LOOP);
        glVertex3f(BOX_SIZE, -BOX_SIZE, BOX_SIZE);
        glVertex3f(BOX_SIZE, -BOX_SIZE, -BOX_SIZE);
        glVertex3f(-BOX_SIZE, -BOX_SIZE, -BOX_SIZE);
        glVertex3f(-BOX_SIZE, -BOX_SIZE, BOX_SIZE);
    glEnd();

    glEnable(GL_LIGHTING);
}

