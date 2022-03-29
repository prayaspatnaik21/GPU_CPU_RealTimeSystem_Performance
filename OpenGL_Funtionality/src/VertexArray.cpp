#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1,&rendererID);
    glBindVertexArray(rendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &rendererID);
}

void VertexArray:: AddBuffer()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);
}

void VertexArray :: Bind()
{
    vb.Bind();
    glBindVertexArray(rendererID);
}

void VertexArray :: UnBind()
{
    vb.UnBind();
    glBindVertexArray(0);
}

