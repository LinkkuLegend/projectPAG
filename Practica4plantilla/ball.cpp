#include "ball.h"


#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

#include <time.h>
#include <cstdlib>
#include <math.h>


Ball::Ball()
{
    _ballPos[0] = 0.0;
    _ballPos[1] = 0.0;
    _ballPos[2] = 0.0;

    //srand (time(NULL));

    _ballSpeed[0] = (float) ((rand()%1000) -500) / 10000;
    _ballSpeed[1] = (float) ((rand()%1000) -500) / 10000;
    _ballSpeed[2] = (float) ((rand()%1000) -500) / 10000;

    _radius = 0.05;
}

void Ball::draw()
{
    glPushMatrix();

    glTranslatef(_ballPos[0], _ballPos[1], _ballPos[2]);

    GLUquadricObj *quadric;
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL );
    gluSphere( quadric , _radius , 36 , 18 );

    gluDeleteQuadric(quadric);

    glPopMatrix();
}

void Ball::animate()
{
    _ballPos[0] += _ballSpeed[0];
    _ballPos[1] += _ballSpeed[1];
    _ballPos[2] += _ballSpeed[2];
}

void Ball::changeDirection()
{
    _ballSpeed[0] *= -1;
    _ballSpeed[1] *= -1;
    _ballSpeed[2] *= -1;
}



int Ball::isInside(Vertex v)
{
    // Calcula si el vértice está dentro de la bola. Devuelve 1 si está dentro, 0 en caso contrario.

    double distance = sqrt((v.x-_ballPos[0])*(v.x-_ballPos[0]) +
                            (v.y-_ballPos[1])*(v.y-_ballPos[1]) +
                            (v.z-_ballPos[2])*(v.z-_ballPos[2]));


    return (distance < _radius);
}


