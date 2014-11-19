#ifndef BALL_H
#define BALL_H

#include "mesh.h"

class Ball
{
    float _ballSpeed[3];
    float _ballPos[3];
    float _radius;
public:
    Ball();

    void draw();
    void animate();

    int isInside(Vertex v);

    float getRadius() {return _radius;}
    float* getPosition() {return _ballPos;}

    void changeDirection();
    void changeDirectionX() {_ballSpeed[0] *= -1;}
    void changeDirectionY() {_ballSpeed[1] *= -1;}
    void changeDirectionZ() {_ballSpeed[2] *= -1;}

};

#endif // BALL_H
