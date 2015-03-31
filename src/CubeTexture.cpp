#include "../include/CubeTexture.h"

using namespace RE;

CubeTexture::CubeTexture()
{
    glGenTextures(1, &object);
    SetWrapMode(GL_CLAMP_TO_EDGE);
    SetScaleMode(GL_LINEAR);

    faceTextures = std::vector<Texture*>(6, nullptr);
}

CubeTexture::~CubeTexture()
{
    glDeleteTextures(1, &object);
}

void CubeTexture::SetWrapMode(GLenum mode)
{
    StateManager::Push();

    Bind();
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, mode);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, mode);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, mode);
    UnBind();

    StateManager::Pop();
}

void CubeTexture::SetScaleMode(GLenum mode)
{
    StateManager::Push();

    Bind();
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, mode);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mode);
    UnBind();

    StateManager::Pop();
}


void CubeTexture::SetFaceTexture(CubeTexture::CubeTextureFace face, Image &image)
{
    StateManager::Push();

    Bind();

    Texture *tex = new Texture();
    tex->SetData(image.GetData(), image.GetWidth(), image.GetHeight(), image.GetFormat(), GL_UNSIGNED_BYTE, GL_RGB);
    faceTextures[face] = tex;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0, GL_RGB, image.GetWidth(), image.GetHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, image.GetData());
    //glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, tex.GetObject()); // FUNCIONARA? :S

    UnBind();

    StateManager::Pop();
}

void CubeTexture::Bind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, object);
}

void CubeTexture::UnBind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeTexture::Bind(GLuint slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, object);
}

void CubeTexture::UnBind(GLuint slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


Texture *CubeTexture::GetFaceTexture(CubeTexture::CubeTextureFace face)
{
    return faceTextures[face];
}
