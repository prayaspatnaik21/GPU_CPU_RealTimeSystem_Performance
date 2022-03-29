#pragma once
#include <GL/glew.h>
#include "VertexBuffer.h"

class VertexArray
{
    private:
        unsigned int rendererID;
        float positions[8] = {-0.5f,-0.5f,
                            0.5f,-0.5f,
                            0.5f,0.5f,
                            -0.5f,0.5f};

        VertexBuffer vb{4*2*sizeof(float)};
    
    public:
        VertexArray();
        ~VertexArray();
        void Bind();
        void UnBind();
        void AddBuffer();
};