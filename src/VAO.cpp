#include "../include/VAO.h"

using namespace RE;


VAO::VAO()
{
    StateManager::Push();

    glEnableClientState(GL_VERTEX_ARRAY);
    glGenVertexArrays(1, &object);
    glDisableClientState(GL_VERTEX_ARRAY);

    StateManager::Pop();
}

VAO::~VAO()
{
    StateManager::Push();

    glEnableClientState(GL_VERTEX_ARRAY);
    glDeleteVertexArrays(1, &object);
    glDisableClientState(GL_VERTEX_ARRAY);

    StateManager::Pop();
}

void VAO::AddAttribute(const VBO &vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint offset) const
{
    StateManager::Push();

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindVertexArray(object);

    glEnableVertexAttribArray(index);
    vbo.Bind();
    glVertexAttribPointer(index, size, type, normalized, stride, (void*) offset);
    vbo.UnBind();

    glBindVertexArray(0);
    glDisableClientState(GL_VERTEX_ARRAY);

    StateManager::Pop();
}

void VAO::Bind() const
{
    glBindVertexArray(object);
}

void VAO::UnBind() const
{
    glBindVertexArray(0);
}

