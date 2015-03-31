#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <stack>
#include "Debug.h"

namespace RE
{

struct GLState
{
    GLint vbo, vao, framebuffer, depthFunc, cullFaceMode, program, texture2d;
    GLboolean depthTest, cullFace, vertexArraysActivated;
};

class StateManager
{
private:

    StateManager() {} //no instances

    static std::stack<GLState> states;

public:

    static void Push();
    static void Pop();
};

}

#endif // STATEMANAGER_H
