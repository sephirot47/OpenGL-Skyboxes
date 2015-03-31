#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#define GL_GLEXT_PROTOTYPES

#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "glm/glm.hpp"
#include "Bindable.h"
#include "Texture.h"
#include "CubeTexture.h"
#include "Shader.h"
#include "Debug.h"
#include "StateManager.h"

namespace RE
{

class ShaderProgram : public Bindable
{
private:

    typedef std::pair<std::string, Texture*> TextureMapPair;
    typedef  std::map<std::string, Texture*> TextureMap;
    typedef std::pair<std::string, CubeTexture*> CubeTextureMapPair;
    typedef  std::map<std::string, CubeTexture*> CubeTextureMap;

    TextureMap textureMap;
    CubeTextureMap cubeTextureMap;
    GLuint object;

public:

    ShaderProgram();
    ~ShaderProgram();

    void AttachShader(const Shader &shader) const;
    void Link() const;
    void Bind() const;
    void UnBind() const;

    void AttachTexture(const std::string name, Texture &texture);
    void AttachTexture(const std::string name, CubeTexture &texture);
    void DetachTexture(const std::string name);

    GLint GetUniformLocation(const std::string name) const;
    void SetUniform(const std::string name, float value) const;
    void SetUniform(const std::string name, int value) const;
    void SetUniform(const std::string name, const glm::vec2& value) const;
    void SetUniform(const std::string name, const glm::vec3& value) const;
    void SetUniform(const std::string name, const glm::vec4& value) const;
    void SetUniform(const std::string name, const glm::mat4& value, GLboolean normalized = GL_FALSE) const;

    GLuint GetObject() const { return object; }
};

}

#endif // SHADERPROGRAM_H
