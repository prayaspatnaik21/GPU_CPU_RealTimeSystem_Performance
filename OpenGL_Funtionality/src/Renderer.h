#include "Shader.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "Headers.h"
#include "VertexArray.h"

class Renderer 
{
    private:

        unsigned int Indices[6] = { 
        0,1,3,
        1,2,3};

        Mat InputImage;

        std::string ShaderPath;

        std::shared_ptr<VertexArray> VertexArrayobject;
        std::shared_ptr<Shader> ShaderObect;
        std::shared_ptr<Texture> TextureObject;
        std::shared_ptr<IndexBuffer> IndexBufferObject;

    public:
        Renderer(Mat image,std::string ShaderPath);
        ~Renderer();

        void Draw();
        void Bind();
        void UnBind();
        void AddBuffer();
        void SetUniformli();
};