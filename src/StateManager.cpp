#include "../include/StateManager.h"

using namespace RE;


std::stack<GLState> StateManager::states;

void StateManager::Push()
{
    GLState s;
    glGetBooleanv(GL_DEPTH_TEST, &s.depthTest);
    glGetBooleanv(GL_CULL_FACE, &s.cullFace);
    glGetBooleanv(GL_VERTEX_ARRAY, &s.vertexArraysActivated);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &s.vbo);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &s.vao);
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &s.framebuffer);
    glGetIntegerv(GL_DEPTH_FUNC, &s.depthFunc);
    glGetIntegerv(GL_CULL_FACE_MODE, &s.cullFaceMode);
    glGetIntegerv(GL_CURRENT_PROGRAM, &s.program);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &s.texture2d);

    states.push(s);
}

void StateManager::Pop()
{
    GLState s = states.top(); states.pop();

    if(s.depthTest) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
    if(s.cullFace) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    if(s.vertexArraysActivated) glEnableClientState(GL_VERTEX_ARRAY); else glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, s.vbo);
    glBindVertexArray(s.vao);
    glBindFramebuffer(GL_FRAMEBUFFER, s.framebuffer);
    glDepthFunc(s.depthFunc);
    glCullFace(s.cullFaceMode);
    glUseProgram(s.program);
    glBindTexture(GL_TEXTURE_2D, s.texture2d);
}
