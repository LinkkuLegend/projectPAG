
#include "octree.h"

#include "ball.h"


#include "time.h"

Octree::Octree()
{

}

void Octree::generate(Mesh* mesh, int level, int minTriangles,const vector<Triangle> &triangles, Vertex center,const vector<double> &size)
{
    //Almacenar parámetros en las variables de la clase (_mesh, _center, _halfX,...)
    _mesh = mesh;
    _center = center;
    _halfX = size[0];
    _halfY = size[1];
    _halfZ = size[2];

    //Clasificar los triangulos que estan dentro del octree
    for (unsigned int i=0; i<triangles.size(); i++)
    {
        if (isInside(triangles[i]))
            _trianglesIncluded.push_back(triangles[i]);
    }


    // Comprobar si se cumple el criterio de parada. Si se cumplen, se ponen los hijos a NULL y se sale del constructor
    if (level == 0 || _trianglesIncluded.size() < minTriangles)
    {
        _children = NULL;
        return;
    }

    // Si no se cumple el criterio de parada, establecer las dimensiones y el centro de los ocho hijos, y generarlos recursivamente
    vector<double> sizeChildren;
    sizeChildren.push_back(_halfX/2);
    sizeChildren.push_back(_halfY/2);
    sizeChildren.push_back(_halfZ/2);
    Vertex childrenCenter;

    _children = new Octree[8];

    childrenCenter.x = _center.x + _halfX/2;
    childrenCenter.y = _center.y + _halfY/2;
    childrenCenter.z = _center.z + _halfZ/2;

    _children[0].generate(_mesh, level-1, minTriangles, _trianglesIncluded, childrenCenter, sizeChildren);



   childrenCenter.x = _center.x - _halfX/2;
   childrenCenter.y = _center.y + _halfY/2;
   childrenCenter.z = _center.z + _halfZ/2;
    _children[1].generate(_mesh, level-1, minTriangles, _trianglesIncluded, childrenCenter, sizeChildren);




    childrenCenter.x = _center.x - _halfX/2;
    childrenCenter.y = _center.y - _halfY/2;
    childrenCenter.z = _center.z + _halfZ/2;
    _children[2].generate(_mesh, level-1, minTriangles, _trianglesIncluded, childrenCenter, sizeChildren);




    childrenCenter.x = _center.x + _halfX/2;
    childrenCenter.y = _center.y - _halfY/2;
    childrenCenter.z = _center.z + _halfZ/2;
    _children[3].generate(_mesh, level-1, minTriangles, _trianglesIncluded, childrenCenter, sizeChildren);






    childrenCenter.x = _center.x + _halfX/2;
    childrenCenter.y = _center.y + _halfY/2;
    childrenCenter.z = _center.z - _halfZ/2;
    _children[4].generate(_mesh, level-1, minTriangles, _trianglesIncluded, childrenCenter, sizeChildren);




    childrenCenter.x = _center.x - _halfX/2;
    childrenCenter.y = _center.y + _halfY/2;
    childrenCenter.z = _center.z - _halfZ/2;
    _children[5].generate(_mesh, level-1, minTriangles, _trianglesIncluded, childrenCenter, sizeChildren);




    childrenCenter.x = _center.x - _halfX/2;
    childrenCenter.y = _center.y - _halfY/2;
    childrenCenter.z = _center.z - _halfZ/2;
    _children[6].generate(_mesh, level-1, minTriangles, _trianglesIncluded, childrenCenter, sizeChildren);


    childrenCenter.x = _center.x + _halfX/2;
    childrenCenter.y = _center.y - _halfY/2;
    childrenCenter.z = _center.z - _halfZ/2;
    _children[7].generate(_mesh, level-1, minTriangles, _trianglesIncluded, childrenCenter, sizeChildren);


}

int Octree::isInside(Triangle t)
{
    // Devuelve 1 si alguno de los puntos del triángulo está dentro de la caja de este nodo del octree. 0 en otro caso.

    Vertex p1 = _mesh->getVertex(t.vertex[0]);
    if ((p1.x>(_center.x - _halfX) && p1.x<(_center.x + _halfX)) &&
        (p1.y>(_center.y - _halfY) && p1.y<(_center.y + _halfY)) &&
        (p1.z>(_center.z - _halfZ) && p1.z<(_center.z + _halfZ)))
            return 1;

    p1 = _mesh->getVertex(t.vertex[1]);
    if ((p1.x>(_center.x - _halfX) && p1.x<(_center.x + _halfX)) &&
        (p1.y>(_center.y - _halfY) && p1.y<(_center.y + _halfY)) &&
        (p1.z>(_center.z - _halfZ) && p1.z<(_center.z + _halfZ)))
            return 1;

    p1 = _mesh->getVertex(t.vertex[2]);
    if ((p1.x>(_center.x - _halfX) && p1.x<(_center.x + _halfX)) &&
        (p1.y>(_center.y - _halfY) && p1.y<(_center.y + _halfY)) &&
        (p1.z>(_center.z - _halfZ) && p1.z<(_center.z + _halfZ)))
            return 1;

    return 0;
}

int Octree::isInside(Ball *ball)
{
    double minPos[3] = {_center.x - _halfX, _center.y - _halfY, _center.z - _halfZ};
    double maxPos[3] = {_center.x + _halfX, _center.y + _halfY, _center.z + _halfZ};
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

int Octree::collide(Ball *ball, vector<Triangle> &collidedTriangles)
{
    if (isInside(ball))
    {
        if (_children == NULL)
        {
            for (int i=0; i<_trianglesIncluded.size(); i++)
            {
                int collide = 0;
                for (int j=0; j<3; j++)
                {

                    if (!collide && ball->isInside(_mesh->getVertex(_trianglesIncluded[i].vertex[j])))
                        collide = 1;

                }
                if (collide)
                {
                    collidedTriangles.push_back(_trianglesIncluded[i]);
                }
            }

            if (!_trianglesIncluded.empty())
                return 1;
        }
        else
        {
            for (int i=0; i<8; i++)
            {

                _children[i].collide(ball, collidedTriangles);
            }
        }
    }


    return !collidedTriangles.empty();
}


void Octree::draw()
{
    // Dibujar el octree
    glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);

    if (_children != NULL)
    {
        for (unsigned int i=0; i<8; i++)
            _children[i].draw();
    }
    else
    {
        //LEFT
        glBegin(GL_LINE_LOOP);
            glVertex3f(_center.x - _halfX, _center.y - _halfY, _center.z - _halfZ);
            glVertex3f(_center.x - _halfX, _center.y + _halfY, _center.z - _halfZ);
            glVertex3f(_center.x - _halfX, _center.y + _halfY, _center.z + _halfZ);
            glVertex3f(_center.x - _halfX, _center.y - _halfY, _center.z + _halfZ);
        glEnd();

        //TOP
        glBegin(GL_LINE_LOOP);
            glVertex3f(_center.x + _halfX, _center.y + _halfY, _center.z + _halfZ);
            glVertex3f(_center.x + _halfX, _center.y + _halfY, _center.z - _halfZ);
            glVertex3f(_center.x - _halfX, _center.y + _halfY, _center.z - _halfZ);
            glVertex3f(_center.x - _halfX, _center.y + _halfY, _center.z + _halfZ);
        glEnd();

        //RIGTH
        glBegin(GL_LINE_LOOP);
            glVertex3f(_center.x + _halfX, _center.y - _halfY, _center.z + _halfZ);
            glVertex3f(_center.x + _halfX, _center.y + _halfY, _center.z + _halfZ);
            glVertex3f(_center.x + _halfX, _center.y + _halfY, _center.z - _halfZ);
            glVertex3f(_center.x + _halfX, _center.y - _halfY, _center.z - _halfZ);
        glEnd();

        //BOTTOM
        glBegin(GL_LINE_LOOP);
            glVertex3f(_center.x + _halfX, _center.y - _halfY, _center.z + _halfZ);
            glVertex3f(_center.x + _halfX, _center.y - _halfY, _center.z - _halfZ);
            glVertex3f(_center.x - _halfX, _center.y - _halfY, _center.z - _halfZ);
            glVertex3f(_center.x - _halfX, _center.y - _halfY, _center.z + _halfZ);
        glEnd();

    }

    glEnable(GL_LIGHTING);
}


