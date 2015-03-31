#include "../include/FrameBuffer.h"

using namespace RE;


FrameBuffer::FrameBuffer(int width, int height)
{
    glGenFramebuffers(1, &object);
    numBuffers = 0;
    this->width = width;
    this->height = height;
}

FrameBuffer::~FrameBuffer()
{
    textures.clear();
    glDeleteFramebuffers(1, &object);

    for(int i = 0; i < numBuffers; ++i) delete textures[i];
}

void FrameBuffer::BindRenderTarget() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, object);
    glDrawBuffers(numBuffers, &drawBuffers[0]);
}

void FrameBuffer::UnBindRenderTarget() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBuffer::AddDrawingBuffer(GLenum attachment,
                                   GLenum format,
                                   GLenum type,
                                   GLint internalFormat,
                                   GLenum wrapMode,
                                   GLenum scaleMode)
{
    StateManager::Push();

    DeleteDrawingBuffer(attachment); //Borralo si ya existia

    ++numBuffers;
    drawBuffers.push_back(attachment);

    Texture *texture = new Texture();
    texture->SetData(0, width, height, format, type, internalFormat);
    texture->SetWrapMode(wrapMode);
    texture->SetScaleMode(scaleMode);
    textures.push_back(texture);

    BindRenderTarget(); //Here glDrawBuffers is called

    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture->GetObject(), 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        DbgError("Error adding the attachment " << attachment << " to the framebuffer.");

    UnBindRenderTarget();

    StateManager::Pop();
}


void FrameBuffer::SetDrawingBuffers(int n, GLenum *attachments) const
{
    glDrawBuffers(n, attachments);
}

bool FrameBuffer::ExistsDrawingBuffer(GLenum attachment) const
{
    for(int i = 0; i < numBuffers; ++i)
        if(drawBuffers[i] == attachment) return true;
    return false;
}

void FrameBuffer::DeleteDrawingBuffer(GLenum attachment)
{
    for(int i = 0; i < numBuffers; ++i)
    {
        if(drawBuffers[i] == attachment)
        {
            --numBuffers;
            drawBuffers.erase(drawBuffers.begin() + i);
            delete textures[i];
            textures.erase(textures.begin() + i);
        }
    }
}

void FrameBuffer::ClearColor() const
{
    StateManager::Push();
    BindRenderTarget();
    glClear(GL_COLOR_BUFFER_BIT);
    UnBindRenderTarget();
    StateManager::Pop();
}

void FrameBuffer::ClearDepth() const
{
    StateManager::Push();
    BindRenderTarget();
    glClear(GL_DEPTH_BUFFER_BIT);
    UnBindRenderTarget();
    StateManager::Pop();
}

void FrameBuffer::ClearColorDepth() const
{
    StateManager::Push();
    BindRenderTarget();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    UnBindRenderTarget();
    StateManager::Pop();
}


Texture *FrameBuffer::GetTexture(GLenum attachment) const
{
    for(int i = 0; i < numBuffers; ++i)
        if(drawBuffers[i] == attachment) return textures[i];
    return nullptr;
}
