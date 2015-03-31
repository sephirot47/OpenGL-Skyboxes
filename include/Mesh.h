#ifndef MESH_H
#define MESH_H

#include "StateManager.h"
#include "RenderTarget.h"
#include "FileLoader.h"
#include "Shader.h"
#include "Debug.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "Material.h"
#include "glm/glm.hpp"

namespace RE
{

class Mesh
{
private:

    Mesh(const Mesh& m){}

    VAO *vao;
    VBO *vboPos, *vboUv, *vboNormals;
    GLenum renderMode;
    glm::mat4 model;

    int numVertices;

public:
    Mesh();
    ~Mesh();

    void LoadFromFile(const char *filepath);
    void LoadPositionsFromArray(const std::vector<glm::vec3> &positions, GLenum renderMode = GL_TRIANGLES);

    void Render(const Material &material, glm::mat4 &camView, glm::mat4 &camProjection);
    void Render(const ShaderProgram &program, glm::mat4 &camView, glm::mat4 &camProjection);
    void Render(RenderTarget &renderTarget, const Material &material, glm::mat4 &camView, glm::mat4 &camProjection);
    void Render(RenderTarget &renderTarget, const ShaderProgram &program, glm::mat4 &camView, glm::mat4 &camProjection);

    void SetRenderMode(GLenum renderMode);
    void SetModelMatrix(glm::mat4 modelMatrix);

    int GetNumVertices() const;
    VAO* GetVAO() const;
    VBO* GetVBOPos() const;
    VBO* GetVBOUv() const;
    VBO* GetVBONormals() const;
    GLenum GetRenderMode() const;
    glm::mat4 GetModelMatrix() const;
};

}

#endif // MESH_H
