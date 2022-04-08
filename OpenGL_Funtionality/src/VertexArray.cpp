#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);
}

VertexArray::~VertexArray(){
glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer()
{
    Bind();
    vb = std::make_shared<VertexBuffer>(positions,5*4*sizeof(float));
    vb->Bind();

    //Location should be the index of the vertex attrib pointer
    //Inedx 0 of this vertex array is bound to currently bound gl array buffer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(3*sizeof(float)));

}
void VertexArray::Bind()
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind()
{
    glBindVertexArray(0);
}