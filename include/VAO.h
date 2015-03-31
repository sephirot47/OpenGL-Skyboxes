#ifndef VAO_H
#define VAO_H
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "VBO.h"
#include "StateManager.h"

namespace RE
{

class VAO : public Bindable
{
private:

    VAO(VAO &vao) {}
    VAO& operator=(const VAO &rhs) { return *this; }

    GLuint object;

public:
    VAO();
    ~VAO();

    void AddAttribute(const VBO &vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint offset) const;

    void Bind() const;
    void UnBind() const;

    GLuint GetObject() const { return object; }
};

}

#endif // VAO_H
