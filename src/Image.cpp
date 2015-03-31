#include "../include/Image.h"

using namespace RE;

Image::Image()
{
    components = width = height = 0;
    data = nullptr;
}

Image::Image(const std::string &filepath) : Image()
{
    LoadFromFile(filepath);
}

Image::~Image()
{
    if(data) delete [] data;
}

void Image::LoadFromFile(const std::string& filepath)
{
    if(data) delete [] data;
    data = FileLoader::ReadImage(filepath.c_str(), components, width, height);
}

int Image::GetSize() const
{
    return width * height * components * sizeof(unsigned char);
}

int Image::GetComponents() const
{
    return components;
}

int Image::GetWidth() const
{
    return width;
}

int Image::GetHeight() const
{
    return height;
}

GLenum Image::GetFormat() const
{
    return components == 3 ? GL_RGB : GL_RGBA;
}

const void* Image::GetData() const
{
    return data;
}
