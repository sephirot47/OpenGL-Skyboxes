#ifndef LIGHT_H
#define LIGHT_H

#include "stb_image.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "GBuffer.h"
#include "Texture.h"
#include "Debug.h"
#include "Mesh.h"
#include "VAO.h"
#include "VBO.h"
#include "StateManager.h"
#include "glm/glm.hpp"

namespace RE
{

enum LightType
{
    DirectionalLight,
    PointLight
};

class Light
{
private:

    static const float screenMesh[12];
    static const std::string vshaderSource;

    VAO *lightVao;
    VBO *lightVbo;
    ShaderProgram *lightProgram, *shadowProgram;
    Shader *lightvshader, *shadowvshader,
           *lightfshader, *shadowfshader;
    FrameBuffer *shadowBuffer;

    glm::vec3 pos, dir;
    glm::vec3 color;
    float intensity, range;
    float shadow;

    bool enabled;

    LightType type;

public:

    Light(LightType type, float screenWidth, float screenHeight);
    ~Light();

    void ClearBufferMeshShadow();
    void ShadowMapMesh(Mesh &m, float screenWidth, float screenHeight);
    void ApplyLight(GBuffer &gbuffer, const glm::mat4 &camView, const glm::mat4 &camProjection) const;

    void SetPosition(glm::vec3 position);
    void SetDirection(glm::vec3 direction);
    void SetColor(glm::vec3 color);
    void SetIntensity(float intensity);
    void SetRange(float range);
    void SetShadow(float shadow);
    void SetEnabled(bool enabled);

    FrameBuffer *GetShadowBuffer() const;
    glm::vec3 GetPosition() const;
    glm::vec3 GetDirection() const;
    glm::vec3 GetColor() const;
    float GetIntensity() const;
    float GetRange() const;
    float GetShadow() const;
    bool GetEnabled() const;

    glm::mat4 GetView() const;
    glm::mat4 GetProjection(float screenWidth, float screenHeight) const;
};

}

#endif // LIGHT_H
