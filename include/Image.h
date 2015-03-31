#ifndef IMAGE_H
#define IMAGE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "Debug.h"
#include "FileLoader.h"

namespace RE
{

class Image
{
private:
    int components, width, height;
    unsigned char *data;

public:
    Image();
    Image(const std::string& filepath);
    ~Image();

    void LoadFromFile(const std::string& filepath);
    int GetSize() const;
    int GetComponents() const;
    int GetWidth() const;
    int GetHeight() const;
    GLenum GetFormat() const;
    const void* GetData() const;
};

}

#endif // IMAGE_H
