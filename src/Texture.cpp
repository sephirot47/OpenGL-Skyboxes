#include "../include/Texture.h"

using namespace RE;

Texture::Texture()
{
    glGenTextures(1, &object);
    SetWrapMode(GL_REPEAT);
    SetScaleMode(GL_LINEAR);
    this->width = 0;
    this->height = 0;
    framebuffer = 0;
}

Texture::Texture(const std::string filepath) : Texture()
{
    LoadFromFile(filepath);
}

Texture::Texture(int width, int height) : Texture()
{
    this->width = width;
    this->height = height;
    CreateEmpty(width, height);
}

Texture::~Texture()
{
    glDeleteTextures(1, &object);
}

void Texture::SetWrapMode(GLenum mode)
{
    StateManager::Push();

    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
    UnBind();

    StateManager::Pop();
}

void Texture::SetScaleMode(GLenum mode)
{
    StateManager::Push();

    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
    UnBind();

    StateManager::Pop();
}

void Texture::BindRenderTarget() const
{
    if(framebuffer == 0)
    {
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, object, 0);

        GLuint depthRenderBuffer;
        glGenRenderbuffers(1, &depthRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLenum drawbuffer = GL_COLOR_ATTACHMENT0; glDrawBuffers(1, &drawbuffer);
}

void Texture::UnBindRenderTarget() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Texture::SetData(const void *data, int width, int height, GLint format, GLenum type, GLint internalFormat)
{
    StateManager::Push();

    Bind();
    this->width = width;
    this->height = height;
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);
    UnBind();

    StateManager::Pop();
}

void Texture::LoadFromFile(const std::string filepath)
{
    Image *img = new Image(); img->LoadFromFile(filepath);
    SetData(img->GetData(), img->GetWidth(), img->GetHeight(), img->GetFormat(), GL_UNSIGNED_BYTE, img->GetFormat());
    delete img;
}

void Texture::CreateEmpty(int width, int height)
{
    this->width = width;
    this->height = height;
    SetData(nullptr, width, height, GL_RGBA, GL_UNSIGNED_BYTE, GL_RGBA);
}

void Texture::CreateEmpty(int width, int height, GLint format, GLenum type, GLint internalFormat)
{
    this->width = width;
    this->height = height;
    SetData(nullptr, width, height, format, type, internalFormat);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, object);
}

void Texture::UnBind() const
{
    glBindTexture(GL_TEXTURE_2D, object);
}

void Texture::Bind(GLuint slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, object);
}

void Texture::UnBind(GLuint slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}
