#include "../include/GBuffer.h"

using namespace RE;

const std::string GBuffer::GColorInputName = "GColor";
const std::string GBuffer::GPositionInputName = "GPosition";
const std::string GBuffer::GUvInputName = "GUv";
const std::string GBuffer::GNormalInputName = "GNormal";
const std::string GBuffer::GMaterialTextureInputName = "GMaterialTexture";
const std::string GBuffer::GMaterialDiffuseInputName = "GMaterialDiffuse";
const std::string GBuffer::GMaterialSpecularInputName = "GMaterialSpecular";
const std::string GBuffer::GMaterialShininessInputName = "GMaterialShininess";
const std::string GBuffer::GDepthInputName = "GDepth";

const float GBuffer::screenMesh[12] = {1.0f, -1.0f, 0.0f,
                                       1.0f,  1.0f, 0.0f,
                                      -1.0f,  1.0f, 0.0f,
                                      -1.0f, -1.0f, 0.0f};

GBuffer::GBuffer(float width, float height) : FrameBuffer(width, height)
{
    this->width = width;
    this->height = height;

    //To render to the screen
    screenMeshVbo = new VBO();
    screenMeshVbo->SetData(GBuffer::screenMesh, sizeof(GBuffer::screenMesh));

    screenMeshVao = new VAO();
    screenMeshVao->AddAttribute(*screenMeshVbo, 0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    vshader = new Shader(); vshader->Create("Assets/Shaders/FrameBuffer/framebuffer.vert", GL_VERTEX_SHADER);
    fshader = new Shader(); fshader->Create("Assets/Shaders/FrameBuffer/framebuffer.frag", GL_FRAGMENT_SHADER);
    program = new ShaderProgram();
    program->AttachShader(*vshader);
    program->AttachShader(*fshader);
    program->Link();
    //

    //Add buffers
    AddDrawingBuffer(GColorAttachment, GL_RGBA, GL_FLOAT, GL_RGBA, GL_REPEAT, GL_NEAREST);
    AddDrawingBuffer(GPositionAttachment, GL_RGBA, GL_FLOAT, GL_RGBA32F, GL_REPEAT, GL_NEAREST);
    AddDrawingBuffer(GUvAttachment, GL_RG, GL_FLOAT, GL_RG, GL_REPEAT, GL_NEAREST);
    AddDrawingBuffer(GNormalAttachment, GL_RGB, GL_FLOAT, GL_RGBA32F, GL_REPEAT, GL_NEAREST);
    AddDrawingBuffer(GMaterialTextureAttachment, GL_RGBA, GL_FLOAT, GL_RGBA, GL_REPEAT, GL_NEAREST);
    AddDrawingBuffer(GMaterialDiffuseAttachment, GL_RGB, GL_FLOAT, GL_RGB, GL_REPEAT, GL_NEAREST);
    AddDrawingBuffer(GMaterialSpecularAttachment, GL_RGB, GL_FLOAT, GL_RGB, GL_REPEAT, GL_NEAREST);
    AddDrawingBuffer(GMaterialShininessAttachment, GL_RGBA, GL_FLOAT, GL_RGBA32F, GL_REPEAT, GL_NEAREST);
    AddDrawingBuffer(GDepthAttachment, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_COMPONENT24, GL_CLAMP_TO_EDGE, GL_NEAREST);
    //

    BindBuffersToProgram(*program);
}

GBuffer::~GBuffer()
{
}

void GBuffer::Render() const
{
    StateManager::Push();

    screenMeshVao->Bind();
    program->Bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_QUADS, 0, 4);

    program->UnBind();
    screenMeshVao->UnBind();

    StateManager::Pop();
}

void GBuffer::RenderToScreen() const
{
    StateManager::Push();

    UnBindRenderTarget();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Render();

    StateManager::Pop();
}

void GBuffer::BindBuffersToProgram(ShaderProgram &program) const
{
    program.AttachTexture(GColorInputName,              *GetGBuffer(GColorAttachment));
    program.AttachTexture(GPositionInputName,           *GetGBuffer(GPositionAttachment));
    program.AttachTexture(GUvInputName,                 *GetGBuffer(GUvAttachment));
    program.AttachTexture(GNormalInputName,             *GetGBuffer(GNormalAttachment));
    program.AttachTexture(GMaterialTextureInputName,    *GetGBuffer(GMaterialTextureAttachment));
    program.AttachTexture(GMaterialDiffuseInputName,    *GetGBuffer(GMaterialDiffuseAttachment));
    program.AttachTexture(GMaterialSpecularInputName,   *GetGBuffer(GMaterialSpecularAttachment));
    program.AttachTexture(GMaterialShininessInputName,  *GetGBuffer(GMaterialShininessAttachment));
    program.AttachTexture(GDepthInputName,              *GetGBuffer(GDepthAttachment));
}

ShaderProgram *GBuffer::GetShaderProgram() const
{
    return program;
}

Texture *GBuffer::GetGBuffer(GBufferAttachment attachment) const
{
    return GetTexture(attachment);
}

float GBuffer::GetWidth() const
{
    return width;
}

float GBuffer::GetHeight() const
{
    return height;
}
