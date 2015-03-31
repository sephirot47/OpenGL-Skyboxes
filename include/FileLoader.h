#ifndef FILELOADER_H
#define FILELOADER_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>

#include "stb_image.h"
#include "Debug.h"
#include "glm/glm.hpp"


namespace RE
{

class FileLoader
{

public:

    static unsigned char* ReadImage(const char *filepath, int &components, int &width, int &height);
    static void GetOBJFormat(const char *filepath, bool &uvs, bool &normals, bool &triangles);
    static bool ReadOBJ(const char *filepath,
                        std::vector<glm::vec3> &vertexPos,
                        std::vector<glm::vec2> &vertexUvs,
                        std::vector<glm::vec3> &vertexNormals,
                        bool &triangles);
};

}

#endif // FILELOADER_H
