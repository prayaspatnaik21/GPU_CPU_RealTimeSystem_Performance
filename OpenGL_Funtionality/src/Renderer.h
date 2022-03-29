#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
    private:
        VertexArray vao;
        IndexBuffer ib;
        Shader shd;

    public:
        Renderer(unsigned int count,std::string path);
        ~Renderer();
        void Bind();
        void UnBind();
        void Draw();
};