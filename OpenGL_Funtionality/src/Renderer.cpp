#include "Renderer.h"

Renderer::Renderer(unsigned count,std::string path)
:vao()
,ib(count)
,shd(path)
{
    vao.AddBuffer();
    int location = shd.GetUniformLocation("u_Color");
}

Renderer::~Renderer()
{
    
}

void Renderer::Bind()
{
    shd.Bind();
    vao.Bind();
    ib.Bind();
}

void Renderer::UnBind()
{
    ib.UnBind();
    vao.UnBind();
    shd.UnBind();
}

void Renderer::Draw()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}