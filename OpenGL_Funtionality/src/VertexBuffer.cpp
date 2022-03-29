#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int size)
{
    glGenBuffers(1,&m_RendererID);
    //Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER,m_RendererID);
    //Static or Dynamic it's upto the type of the Application
    glBufferData(GL_ARRAY_BUFFER,size,positions,GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER,m_RendererID);
}

void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}