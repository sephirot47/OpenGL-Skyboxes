#ifndef SHADER_H
#define SHADER_H

#define GL_GLEXT_PROTOTYPES

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "StateManager.h"
#include "Debug.h"

namespace RE
{

class Shader
{
private:

    Shader(const Shader& s) { }
    Shader& operator=(const Shader &s) { return *this; }
    GLuint object;

public:

    Shader();
    ~Shader();

    bool Create(const std::string filepath, GLuint type);
    bool CreateFromSourceCode(const std::string code, GLuint type);
    GLuint GetObject() const { return object; }
};

}

#endif // SHADER_H
