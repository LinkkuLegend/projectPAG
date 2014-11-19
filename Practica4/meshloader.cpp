#include "meshloader.h"
#include <fstream>
#include <sstream>

MeshLoader::MeshLoader()
{

}

int MeshLoader::loadOBJ(string path)
{
    _mesh = new Mesh();

    string aux;

    ifstream ifs(path.c_str());
    string buffer;

    Vertex center;
    center.x = 0.0;
    center.y = 0.0;
    center.z = 0.0;


    ifs.open(path.c_str());
    ifs.clear();

    if (!ifs.is_open())
    {
        return -1;
    }



    string id, ind1, ind2, ind3, temp;
    double dato1, dato2, dato3;

    while (!ifs.eof())
    {
        getline(ifs, buffer);
        istringstream bufferStream(buffer);

        aux = buffer.substr(0,2);
        if (aux == "v ")
        {
            bufferStream >> id >> dato1 >> dato2 >> dato3;
            _mesh->addVertex(dato1, dato2, dato3);

            center.x += dato1;
            center.y += dato2;
            center.z += dato3;
        } else if (aux == "f ")
        {
            bufferStream >> id >> ind1 >> ind2 >> ind3;

            temp = getSubstring(ind1, "/", 1);
            bufferStream.str(temp);
            bufferStream.clear();
            bufferStream >> dato1;

            bufferStream.ignore(1);

            temp = getSubstring(ind2, "/", 1);
            bufferStream.str(temp);
            bufferStream.clear();
            bufferStream >> dato2;

            bufferStream.ignore(1);

            temp = getSubstring(ind3, "/", 1);
            bufferStream.str(temp);
            bufferStream.clear();
            bufferStream >> dato3;


            _mesh->addTriangle(dato1-1, dato2-1, dato3-1);

        }

    }


    center.x /= _mesh->getNumVertices();
    center.y /= _mesh->getNumVertices();
    center.z /= _mesh->getNumVertices();

    _mesh->setPosition(center.x, center.y, center.z);

    return 0;

}

string MeshLoader::getSubstring(string s, string character, int num)
{
    int i=1, pos_ini=0, pos_fin=0;

    while (i<num)
    {
        pos_ini = s.find(character, pos_ini);
        pos_ini++;
        i++;
    }
    pos_fin = s.find(character, pos_ini);
    if (pos_fin == -1)
    {
        pos_fin = s.size();
    }

    if (num > 1 && pos_ini == 0)
        return "";

    if (pos_fin > pos_ini)
        return s.substr(pos_ini, pos_fin-pos_ini);

    return "";
}
