#include "../include/Mesh.h"

using namespace RE;


Mesh::Mesh()
{
    numVertices = 0;
    model = glm::mat4(1.0f);
    vao = nullptr;
    vboPos = vboUv = vboNormals = nullptr;
}

Mesh::~Mesh()
{
    if(vao) delete vao;
    if(vboPos) delete vboPos;
    if(vboUv) delete vboUv;
    if(vboNormals) delete vboNormals;
}

void Mesh::LoadFromFile(const char *filepath)
{
    StateManager::Push();

    if(vao) delete vao;
    if(vboPos) delete vboPos;
    if(vboUv) delete vboUv;
    if(vboNormals) delete vboNormals;

    std::vector<glm::vec3> pos, normals;
    std::vector<glm::vec2> uv;
    bool triangles;

    FileLoader::ReadOBJ(filepath, pos, uv, normals, triangles);

    renderMode = triangles ? GL_TRIANGLES : GL_QUADS;
    numVertices = pos.size();

    vao = new VAO();
    int index = 0;
    if(pos.size() > 0)
    {
        vboPos = new VBO();
        vboPos->SetData(&pos[0], pos.size() * sizeof(glm::vec3));
        vao->AddAttribute(*vboPos, index++, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if(uv.size() > 0)
    {
        vboUv = new VBO();
        vboUv->SetData(&uv[0], uv.size() * sizeof(glm::vec2));
        vao->AddAttribute(*vboUv, index++, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if(normals.size() > 0)
    {
        vboNormals = new VBO();
        vboNormals->SetData(&normals[0], normals.size() * sizeof(glm::vec3));
        vao->AddAttribute(*vboNormals, index++, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    DbgLog(numVertices);

    StateManager::Pop();
}

void Mesh::LoadPositionsFromArray(const std::vector<glm::vec3> &positions, GLenum renderMode)
{
    StateManager::Push();

    if(vboPos) delete vboPos;

    numVertices = positions.size();

    if(not vao) vao = new VAO();
    int index = 0;
  //  if(vboUv) ++index;
  //  if(vboNormals) ++index;

    vboPos = new VBO();
    vboPos->SetData(&positions[0], positions.size() * sizeof(glm::vec3));
    vao->AddAttribute(*vboPos, index, 3, GL_FLOAT, GL_FALSE, 0, 0);

    this->renderMode = renderMode;
    DbgLog(numVertices);

    StateManager::Pop();
}

void Mesh::Render(RenderTarget &renderTarget, const Material &material, glm::mat4 &camView, glm::mat4 &camProjection)
{
    StateManager::Push();

    renderTarget.BindRenderTarget();
        Render(material, camView, camProjection);
    renderTarget.UnBindRenderTarget();

    StateManager::Pop();
}

void Mesh::Render(RenderTarget &renderTarget, const ShaderProgram &program, glm::mat4 &camView, glm::mat4 &camProjection)
{
    StateManager::Push();

    renderTarget.BindRenderTarget();
        Render(program, camView, camProjection);
    renderTarget.UnBindRenderTarget();

    StateManager::Pop();
}

void Mesh::Render(const Material &material, glm::mat4 &camView, glm::mat4 &camProjection)
{
    if(not vao) return;

    StateManager::Push();

    material.Bind();
        Render(*material.GetShaderProgram(), camView, camProjection);
    material.UnBind();

    StateManager::Pop();
}

void Mesh::Render(const ShaderProgram &program, glm::mat4 &camView, glm::mat4 &camProjection)
{
    if(not vao) return;

    StateManager::Push();

    vao->Bind();

        program.Bind();

            program.SetUniform("projection", camProjection);
            program.SetUniform("view", camView);
            program.SetUniform("model", model);
            program.SetUniform("normalMatrix", glm::transpose(glm::inverse(camView * model)));
            program.SetUniform("PVM", camProjection * camView * model);

            glDrawArrays(renderMode, 0, numVertices);

        program.UnBind();

    vao->UnBind();

    StateManager::Pop();
}

void Mesh::SetRenderMode(GLenum renderMode)
{
    this->renderMode = renderMode;
}

void Mesh::SetModelMatrix(glm::mat4 modelMatrix)
{
    this->model = modelMatrix;
}


int Mesh::GetNumVertices() const
{
    return numVertices;
}

VAO* Mesh::GetVAO() const
{
    return vao;
}

VBO* Mesh::GetVBOPos() const
{
    return vboPos;
}

VBO* Mesh::GetVBOUv() const
{
    return vboUv;
}

VBO* Mesh::GetVBONormals() const
{
    return vboNormals;
}

GLenum Mesh::GetRenderMode() const
{
    return renderMode;
}

glm::mat4 Mesh::GetModelMatrix() const
{
    return model;
}
