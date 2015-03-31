#include "../include/Shader.h"

using namespace RE;


Shader::Shader()
{
    object = 0;
}

Shader::~Shader()
{
    if(object == 0) return;
    glDeleteShader(object);
}

bool Shader::Create(const std::string filepath, GLuint type)
{
    object = glCreateShader(type);

    FILE *f = fopen(filepath.c_str(), "r");
    if(f == NULL) { DbgError("Error opening the shader file " << filepath); return false; }

    fseek(f, 0, SEEK_END);
    int srcCodeLength = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *srcCodeC = new char[srcCodeLength+1];
    int readres = fread(srcCodeC, sizeof(char), srcCodeLength, f);
    srcCodeC[srcCodeLength] = '\0';

    object = glCreateShader(type);
    glShaderSource(object, 1, &srcCodeC, &srcCodeLength);
    delete[] srcCodeC;

    glCompileShader(object);

    int compilationResult;
    glGetShaderiv(object, GL_COMPILE_STATUS, &compilationResult);

    if(compilationResult == GL_FALSE)
    {
        char shaderErrorLog[1000];
        glGetShaderInfoLog(object, 1000, 0, shaderErrorLog);
        DbgError("'" << filepath << "'' contains errors! It can't be compiled:" << shaderErrorLog);
        glDeleteShader(object);
        return false;
    }
    return true;
}

bool Shader::CreateFromSourceCode(const std::string code, GLuint type)
{
    object = glCreateShader(type);

    int srcCodeLength = code.length();

    char *srcCodeC = new char[srcCodeLength+1];
    strcpy(srcCodeC, code.c_str());
    srcCodeC[srcCodeLength] = '\0';

    object = glCreateShader(type);
    glShaderSource(object, 1, &srcCodeC, &srcCodeLength);
    delete[] srcCodeC;

    glCompileShader(object);

    int compilationResult;
    glGetShaderiv(object, GL_COMPILE_STATUS, &compilationResult);

    if(compilationResult == GL_FALSE)
    {
        char shaderErrorLog[1000];
        glGetShaderInfoLog(object, 1000, 0, shaderErrorLog);
        DbgError("The shader contains errors! It can't be compiled:" << shaderErrorLog);
        glDeleteShader(object);
        return false;
    }
    return true;
}
