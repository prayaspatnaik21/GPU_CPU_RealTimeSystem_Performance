#include "VertexBuffer.h"
#include <memory>


class VertexArray{

    private:
        float positions[25] = {0.5f,0.5f,0.0f,1.0f,1.0f,
                            0.5f,-0.5f,0.0f, 1.0f,0.0f,
                            -0.5f,-0.5f,0.0f,0.0f,0.0f,
                            -0.5f,0.5f,0.0f, 0.0f,1.0f};

        std::shared_ptr<VertexBuffer> vb;
        unsigned int m_RendererID;
    public:
        VertexArray();
        ~VertexArray();
        void AddBuffer();
        void Bind();
        void UnBind();
};