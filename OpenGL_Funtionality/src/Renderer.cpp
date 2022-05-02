#include "Renderer.h"


Renderer::Renderer(std::string shaderPath,glm::mat4 trans)
    :ShaderPath(shaderPath),
    TransformationMatrix(trans)
{
    VertexArrayobject=std::make_shared<VertexArray>();
    ShaderObject=std::make_shared<Shader>(ShaderPath);
    IndexBufferObject=std::make_shared<IndexBuffer>(Indices,6);
}

Renderer:: ~Renderer()
{
}

void Renderer::Draw()
{
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
}

void Renderer::Bind()
{
    ShaderObject->Bind();
    VertexArrayobject->Bind();
    IndexBufferObject->Bind();
}

void Renderer::UnBind()
{
    ShaderObject->UnBind();
    VertexArrayobject->UnBind();
    IndexBufferObject->UnBind();
}

void Renderer::AddBuffer()
{
    VertexArrayobject->AddBuffer();
}

void  Renderer::SetUniformli(bool rotationEnable)
{
    ShaderObject->SetUniform1i("u_Texture",0);
    if(rotationEnable)
        ShaderObject->SetUniformMatrix4fv("transform",TransformationMatrix);
}