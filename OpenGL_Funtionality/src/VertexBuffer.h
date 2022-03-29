#pragma once
#include <GL/glew.h>

class VertexBuffer
{
    private:
        unsigned int m_RendererID;
        float positions[8] = {-0.5f,-0.5f,
                            0.5f,-0.5f,
                            0.5f,0.5f,
                            -0.5f,0.5f};

    public:
        VertexBuffer(unsigned int size);
        ~VertexBuffer();
        void Bind() const;
        void UnBind() const;
};