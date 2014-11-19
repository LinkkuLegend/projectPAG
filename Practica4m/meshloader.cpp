#include "meshloader.h"
#include <fstream>
#include <sstream>

MeshLoader::MeshLoader()
{
    _mesh = new Mesh;
}

int MeshLoader::loadOBJ(string path)
{
    //Construye la malla _mesh a partir del .obj localizado en path (Práctica 2)
    ifstream file(path.data());

    if (!file) {
        //cout << "Unable to open file";
        return 0;
    }

    Vertex center;
    center.x = 0.0;
    center.y = 0.0;
    center.z = 0.0;

    std::string s;
    while (std::getline(file, s)){

        //Comprobar si es un vertice
        if(s.substr(0,2) == "v "){
            std::istringstream v(s.substr(2));
            double x,y,z;
            v>>x;v>>y;v>>z;
            _mesh->addVertex(x,y,z);

            center.x += x;
            center.y += y;
            center.z += z;
        }

        //Comprobar si es una cara
        if(s.substr(0,2) == "f "){
            std::istringstream f(s.substr(2));
            int x,y,z;
            f>>x;f>>y;f>>z;
            _mesh->addTriangle(x-1,y-1,z-1);
        }
    }

    center.x /= _mesh->getNumVertices();
    center.y /= _mesh->getNumVertices();
    center.z /= _mesh->getNumVertices();

    _mesh->setPosition(center.x, center.y, center.z);
    file.close();

    return 1;

}
