#include "Shader.h"

Shader::Shader(std::string shaderPath)
:ShaderPath(shaderPath)
{
    ShaderProgramSource source = ReadShader(ShaderPath);
    ShaderID = CreateShader(source.VertexSource,source.FragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(ShaderID);
}

ShaderProgramSource Shader :: ReadShader(const std::string filePath)
{
    std::ifstream stream(filePath);
    enum class ShaderType
    {
        NONE = -1,VERTEX = 0,FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else{
            ss[(int)type]  << line << "\n";
        }
    }

    return { ss[0].str(),ss[1].str()};
}

unsigned int Shader :: CompileShader(unsigned int type,const std::string source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE){
        int length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)malloc(length * sizeof(char)); // stack Dynamically
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << " " <<
                    (type == GL_VERTEX_SHADER ? "vertex":"fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader :: CreateShader(const std::string vertexShader, const std::string fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShaderID = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);


    glAttachShader(program, vertexShaderID);
    glAttachShader(program, fragmentShaderID);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return program;
}

void Shader :: Bind()
{
    glUseProgram(ShaderID);
}

void Shader :: UnBind()
{
    glUseProgram(0);
}

int Shader :: GetUniformLocation(std::string uniformName){
    return glGetUniformLocation(ShaderID, uniformName.c_str());
}

void Shader :: SetUniformLocation(int location,float r,float g,float b)
{
    glUniform4f(location,r,g,b,0.0f);
}

void Shader :: SetUniform1i(const std::string& name , int val)
{
    glUniform1i(GetUniformLocation(name),val);
}

void Shader ::  SetUniformMatrix4fv(const std::string& uniformName , const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
}