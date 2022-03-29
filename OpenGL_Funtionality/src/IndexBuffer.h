#pragma once
#include <GL/glew.h>

class IndexBuffer
{
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
        unsigned int indices[6] = { 0,1,
                                    2,2,3,0};

    public:
        IndexBuffer(unsigned int count);
        ~IndexBuffer();

        void Bind() const;
        void UnBind() const;

        inline unsigned int GetCount() const{ return m_Count; }
};