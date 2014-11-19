#include "viewer.h"
#include "meshloader.h"


Viewer::Viewer()
{
    _mesh = NULL;
    _boundingBox = NULL;
    _octree = NULL;
    type = 1;
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

    float* ballPos = _ball.getPosition();
    float radius = _ball.getRadius();
    if (ballPos[0] + radius > BOX_SIZE || ballPos[0] - radius < -BOX_SIZE)
        _ball.changeDirectionX();

    if (ballPos[1] + radius > BOX_SIZE || ballPos[1] - radius < -BOX_SIZE)
        _ball.changeDirectionY();

    if (ballPos[2] + radius > BOX_SIZE || ballPos[2] - radius < -BOX_SIZE)
        _ball.changeDirectionZ();

    // Calcular colision malla - bola y almacenar los triangulos que colisionan en _collidedTriangles


    if (_boundingBox != NULL)
    if (_boundingBox->collide(&_ball)){
        _collidedTriangles.clear();
        switch (type) {
        case 0:
            _mesh->collide(&_ball,_collidedTriangles);
            break;
        case 1:
            _octree->collide(&_ball, _collidedTriangles);
            break;
        }
    }
}

void Viewer::draw()
{
    // Pintar los triangulos que colisionan (_collidedTriangles)

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
        for(unsigned i=0; i<_collidedTriangles.size(); i++)
        {
            glNormal3f(_collidedTriangles[i].normal.nx, _collidedTriangles[i].normal.ny, _collidedTriangles[i].normal.nz);
            glVertex3f(_mesh->getVertex(_collidedTriangles[i].vertex[0]).x, _mesh->getVertex(_collidedTriangles[i].vertex[0]).y, _mesh->getVertex(_collidedTriangles[i].vertex[0]).z);
            glVertex3f(_mesh->getVertex(_collidedTriangles[i].vertex[1]).x, _mesh->getVertex(_collidedTriangles[i].vertex[1]).y, _mesh->getVertex(_collidedTriangles[i].vertex[1]).z);
            glVertex3f(_mesh->getVertex(_collidedTriangles[i].vertex[2]).x, _mesh->getVertex(_collidedTriangles[i].vertex[2]).y, _mesh->getVertex(_collidedTriangles[i].vertex[2]).z);
        }
    glEnd();



    glColor3f(1.0, 1.0, 1.0);
    if(_collidedTriangles.size() == 0)
        _ball.draw();
    drawBox();

    if (_mesh)
        _mesh->draw();

    if (_boundingBox)
        _boundingBox->draw();

    /*if (_octree)
        _octree->draw();*/

    //


}


void Viewer::init()
{
    //startAnimation();
}






int Viewer::getType() const
{
    return type;
}

void Viewer::setType(int value)
{
    type = value;
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

