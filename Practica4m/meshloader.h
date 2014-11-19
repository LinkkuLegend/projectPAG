#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <string>
#include "mesh.h"

using namespace std;

class MeshLoader
{
    Mesh* _mesh;
public:
    MeshLoader();

    int loadOBJ(string path);
    Mesh* getMesh() {return _mesh;}
};

#endif // MESHLOADER_H
