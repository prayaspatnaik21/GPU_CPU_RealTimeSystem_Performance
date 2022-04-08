#include "Renderer.h"


Renderer::Renderer(Mat image,std::string shaderPath,glm::mat4 trans)
    :InputImage(image),
    ShaderPath(shaderPath),
    TransformationMatrix(trans)
{
    VertexArrayobject=std::make_shared<VertexArray>();
    ShaderObject=std::make_shared<Shader>(ShaderPath);
    TextureObject=std::make_shared<Texture>(InputImage);
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
    TextureObject->Bind(0);
    ShaderObject->Bind();
    VertexArrayobject->Bind();
    IndexBufferObject->Bind();
}

void Renderer::UnBind()
{
    TextureObject->UnBind();
    ShaderObject->UnBind();
    VertexArrayobject->UnBind();
    IndexBufferObject->UnBind();
}

void Renderer::AddBuffer()
{
    VertexArrayobject->AddBuffer();
}

void  Renderer::SetUniformli()
{
    ShaderObject->SetUniform1i("u_Texture",0);
    ShaderObject->SetUniformMatrix4fv("transform",TransformationMatrix);
}