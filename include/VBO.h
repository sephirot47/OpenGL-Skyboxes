#ifndef VBO_H
#define VBO_H

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "Bindable.h"
#include "StateManager.h"

namespace RE
{

class VBO : public Bindable
{
private:
    VBO(VBO &vbo) {}
    VBO& operator=(const VBO &rhs) { return *this; }
    GLuint object;

public:
    VBO();
    ~VBO();

    void SetData(const void *data, int size) const;
    void Bind() const;
    void UnBind() const;

    GLuint GetObject() const { return object; }
};

}

#endif // VBO_H
