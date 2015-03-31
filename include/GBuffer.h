#ifndef GBUFFER_H
#define GBUFFER_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>

#include "StateManager.h"
#include "stb_image.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "FrameBuffer.h"
#include "Texture.h"
#include "Debug.h"
#include "VAO.h"
#include "VBO.h"
#include "glm/glm.hpp"

namespace RE
{

class GBuffer : public FrameBuffer
{
private:

    static const std::string GColorInputName;
    static const std::string GPositionInputName;
    static const std::string GUvInputName;
    static const std::string GNormalInputName;
    static const std::string GMaterialTextureInputName;
    static const std::string GMaterialDiffuseInputName;
    static const std::string GMaterialSpecularInputName;
    static const std::string GMaterialShininessInputName;
    static const std::string GDepthInputName;

    static const float screenMesh[12];

    VAO *screenMeshVao;
    VBO *screenMeshVbo;
    ShaderProgram *program;
    Shader *vshader, *fshader;
    float width, height;

public:

    enum GBufferAttachment
    {
        GColorAttachment = GL_COLOR_ATTACHMENT0,
        GPositionAttachment = GL_COLOR_ATTACHMENT1,
        GUvAttachment = GL_COLOR_ATTACHMENT2,
        GNormalAttachment = GL_COLOR_ATTACHMENT3,
        GMaterialTextureAttachment = GL_COLOR_ATTACHMENT4,
        GMaterialDiffuseAttachment = GL_COLOR_ATTACHMENT5,
        GMaterialSpecularAttachment = GL_COLOR_ATTACHMENT6,
        GMaterialShininessAttachment = GL_COLOR_ATTACHMENT7,
        GDepthAttachment = GL_DEPTH_ATTACHMENT
    };

    GBuffer(float width, float height);
    ~GBuffer();

    void Render() const;
    void RenderToScreen() const;

    void BindBuffersToProgram(ShaderProgram &program) const;

    VAO *GetVAO() const;
    ShaderProgram *GetShaderProgram() const;
    Texture *GetGBuffer(GBufferAttachment attachment) const;

    float GetWidth() const;
    float GetHeight() const;
};

}

#endif // GBUFFER_H
