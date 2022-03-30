#pragma once
#include "Renderer.h"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
    private:
        std::string ShaderPath;
        unsigned int ShaderID;
    public:
        Shader(std::string shaderPath);
        ~Shader();
        ShaderProgramSource ReadShader(const std::string filePath);
        unsigned int CompileShader(unsigned int type,const std::string source);
        unsigned int CreateShader(const std::string vertexShader, const std::string fragmentShader);
        void Bind();
        void UnBind();
        int GetUniformLocation(std::string uniformName);
        void SetUniformLocation(int location,int r,int g,int b);
};