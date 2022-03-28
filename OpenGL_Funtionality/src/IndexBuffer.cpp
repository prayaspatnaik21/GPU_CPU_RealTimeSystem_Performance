#include "IndexBuffer.h"
#include  "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data,unsigned int count)
    :m_Count(count)
{
    glGenBuffers(1,&m_RendererID);
    //Bind the buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID);
    //Static or Dynamic it's upto the type of the Application
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(unsigned int),data,GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1,&m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID);
}

void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}