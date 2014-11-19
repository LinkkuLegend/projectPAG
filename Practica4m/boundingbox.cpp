#include "boundingbox.h"

BoundingBox::BoundingBox(Mesh* mesh)
{
    // Generar la caja envolvente de la malla (Práctica 2)
    GLdouble x, y, z;

    _minX = _maxX = mesh->getVertex(0).x;
    _minY = _maxY = mesh->getVertex(0).y;
    _minZ = _maxZ = mesh->getVertex(0).z;

    // Generar la caja envolvente de la malla
    for(int i = 0; i < mesh->getNumVertices(); i++){
            x = mesh->getVertex(i).x;
            y = mesh->getVertex(i).y;
            z = mesh->getVertex(i).z;

            if(x > _maxX)
                _maxX = x;
            if(x < _minX)
                _minX = x;

            if(y > _maxY)
                _maxY = y;
            if(y < _minY)
                _minY = y;

            if(z > _maxZ)
                _maxZ = z;
            if(z < _minZ)
                _minZ = z;

    }
}


void BoundingBox::draw()
{
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);

    //LEFT
    glBegin(GL_LINE_LOOP);
        glVertex3f(_minX, _minY, _minZ);
        glVertex3f(_minX, _maxY, _minZ);
        glVertex3f(_minX, _maxY, _maxZ);
        glVertex3f(_minX, _minY, _maxZ);
    glEnd();

    //TOP
    glBegin(GL_LINE_LOOP);
        glVertex3f(_maxX, _maxY, _maxZ);
        glVertex3f(_maxX, _maxY, _minZ);
        glVertex3f(_minX, _maxY, _minZ);
        glVertex3f(_minX, _maxY, _maxZ);
    glEnd();

    //RIGTH
    glBegin(GL_LINE_LOOP);
        glVertex3f(_maxX, _minY, _maxZ);
        glVertex3f(_maxX, _maxY, _maxZ);
        glVertex3f(_maxX, _maxY, _minZ);
        glVertex3f(_maxX, _minY, _minZ);
    glEnd();

    //BOTTOM
    glBegin(GL_LINE_LOOP);
        glVertex3f(_maxX, _minY, _maxZ);
        glVertex3f(_maxX, _minY, _minZ);
        glVertex3f(_minX, _minY, _minZ);
        glVertex3f(_minX, _minY, _maxZ);
    glEnd();



   glEnable(GL_LIGHTING);
}



Vertex BoundingBox::getCenter()
{
    // Devuelve el punto central de la caja envolvente

    Vertex center;
    center.x = (_maxX+_minX)/2;
    center.y = (_maxY+_minY)/2;
    center.z = (_maxZ+_minZ)/2;


    return center;
}

vector<double> BoundingBox::getHalfSize()
{
    //Devuelve un vector con la mitad del tamaño de la caja en cada dimensión: {_halfX, _halfY, _halfZ}

    vector<double> returnedValue;

    returnedValue.push_back((_maxX - _minX)/2);
    returnedValue.push_back((_maxY - _minY)/2);
    returnedValue.push_back((_maxZ - _minZ)/2);

    return returnedValue;
}



int BoundingBox::collide(Ball* ball)
{
    double minPos[3] = {_minX, _minY, _minZ};
    double maxPos[3] = {_maxX, _maxY, _maxZ};
    double s = 0.0;
    double d = 0.0;
    for (int i = 0; i < 3; ++i)
    {
        if (ball->getPosition()[i] < minPos[i])
        {
            s = ball->getPosition()[i] - minPos[i];
            d += s * s;
        }
        else
            if (ball->getPosition()[i] > maxPos[i])
            {
                s = ball->getPosition()[i] - maxPos[i];
                d += s * s;
            }
    }

    return (d <= ball->getRadius() * ball->getRadius());
}
