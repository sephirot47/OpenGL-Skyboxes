#include "../include/ShaderProgram.h"

using namespace RE;


ShaderProgram::ShaderProgram()
{
    object = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    if(object == 0) return;
    glDeleteProgram(object);
}

void ShaderProgram::AttachShader(const Shader &shader) const
{
    glAttachShader(object, shader.GetObject());
}

void ShaderProgram::Link() const
{
    glLinkProgram(object);

    // Check the program
    int infoLogLength = 0, result = GL_FALSE;
    glGetProgramiv(object, GL_LINK_STATUS, &result);
    if(result == GL_FALSE)
    {
        glGetProgramiv(object, GL_INFO_LOG_LENGTH, &infoLogLength);
        if(infoLogLength < 1) infoLogLength = 1;
        char* errormsg = new char[infoLogLength];
        glGetProgramInfoLog(object, infoLogLength, NULL, errormsg);
        DbgError("Error linking shader program: " << errormsg);
        delete [] errormsg;
    }
}

void ShaderProgram::Bind() const
{
    glUseProgram(object);

    int slot = 0;
    for(auto it : textureMap)
    {
        it.second->Bind(slot);
        glUniform1i(GetUniformLocation(it.first), slot);
        ++slot;
    }

    for(auto it : cubeTextureMap)
    {
        it.second->Bind(slot);
        glUniform1i(GetUniformLocation(it.first), slot);
        ++slot;
    }
}

void ShaderProgram::UnBind() const
{
    glUseProgram(0);

    int slot = 0;
    for(auto it : textureMap)
    {
        Texture::UnBind(slot);
        ++slot;
    }

    for(auto it : cubeTextureMap)
    {
        CubeTexture::UnBind(slot);
        ++slot;
    }
}

void ShaderProgram::AttachTexture(const std::string name, Texture &texture)
{
    auto it = textureMap.find(name);
    if(it != textureMap.end()) textureMap.erase(it);
    textureMap.insert( textureMap.end(), TextureMapPair(name, &texture) );
}

void ShaderProgram::AttachTexture(const std::string name, CubeTexture &texture)
{
    auto it = cubeTextureMap.find(name);
    if(it != cubeTextureMap.end()) cubeTextureMap.erase(it);
    cubeTextureMap.insert( cubeTextureMap.end(), CubeTextureMapPair(name, &texture) );
}

void ShaderProgram::DetachTexture(const std::string name)
{
    auto it = textureMap.find(name);
    if(it != textureMap.end()) textureMap.erase(it);
    else
    {
        auto it = cubeTextureMap.find(name);
        if(it != cubeTextureMap.end()) cubeTextureMap.erase(it);
    }
}


GLint ShaderProgram::GetUniformLocation(const std::string name) const
{
    return glGetUniformLocation(object, name.c_str());
}

void ShaderProgram::SetUniform(const std::string name, float value) const
{
    StateManager::Push();
    Bind();
    glUniform1f(GetUniformLocation(name), value);
    StateManager::Pop();
}

void ShaderProgram::SetUniform(const std::string name, int value) const
{
    StateManager::Push();
    Bind();
    glUniform1i(GetUniformLocation(name), value);
    StateManager::Pop();
}

void ShaderProgram::SetUniform(const std::string  name, const glm::vec2 &value) const
{
    StateManager::Push();
    Bind();
    glUniform2f(GetUniformLocation(name), value.x, value.y);
    StateManager::Pop();
}

void ShaderProgram::SetUniform(const std::string  name, const glm::vec3 &value) const
{
    StateManager::Push();
    Bind();
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    StateManager::Pop();
}

void ShaderProgram::SetUniform(const std::string  name, const glm::vec4 &value) const
{
    StateManager::Push();
    Bind();
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    StateManager::Pop();
}

void ShaderProgram::SetUniform(const std::string  name, const glm::mat4 &value, GLboolean normalized) const
{
    StateManager::Push();
    Bind();
    glUniformMatrix4fv(GetUniformLocation(name), 1, normalized, glm::value_ptr(value));
    StateManager::Pop();
}

