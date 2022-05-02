#include "Headers.h"
#include "Renderer.h"
#include "Texture.h"
#include "Transformation.h"
using namespace std::chrono;

using namespace cv;

int main(void)
{
    std::cout << "Choose the type of Shader\n"
            "GreyScale Shader 1\n"
            "Guassian Filter shader 2\n"
            "Rotation Shader 3"<<std::endl;

    int chooseShader{0};
    std::cin >> chooseShader;

    std::string shaderPath  = " ";

    bool RotateImageOperation = false;

    switch(chooseShader)
    {
        case 1:
            shaderPath = "../resources/shaders/shaderGrey.shader";
            break;
        case 2:
            shaderPath = "../resources/shaders/shaderGaussian.shader";
            break;
        case 3:
            RotateImageOperation = true;
            shaderPath = "../resources/shaders/shaderRotation.shader";
            break;
        default:
            shaderPath = "../resources/shaders/shaders.shader"; 
    }
   
    int i{0};

    while(i < 5)
	{
        std::string fixedPath = "../resources/Images/Sam_";
	    std::string VariableFileName;

        VariableFileName = std::to_string(i)+ ".jpg";
        std::string ResultPath = fixedPath + VariableFileName;

        Mat image = imread(ResultPath,1);

        cv::imshow(" image", image);
        cv::waitKey(0);

        /*---------------------------------------------------------------------------------------------------------------------------------------*/

        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;

        if(!glewInit())
            return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(image.cols, image.rows, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);

        glfwSwapInterval(1);

        //Setting glewExperimental to true ensures GLEW uses more modern techniques for managing OpenGL functionality
        glewExperimental = GL_TRUE;

        if(glewInit() != GLEW_OK)
            std::cout << "Error!" << std::endl;

        std::cout << glGetString(GL_VERSION) << std::endl;

        std::cout << "Image Resolution" << " " << image.cols << "X" << image.rows << std::endl;
        flip(image,image,0);
        
    /*we want to render a single triangle we want to specify a total of three vertices with
    each vertex having a 3D position. */

        unsigned int indices[] = { 
            0,1,3,
            1,2,3
        };

        Transformation Transform;
        glm::mat4 RotationMatrix  = glm::mat4(1.0f);

        if(RotateImageOperation)
            RotationMatrix = Transform.GetRotationMatrix(90.0f);

        Renderer RendererObject(shaderPath,RotationMatrix);
        RendererObject.AddBuffer();
        RendererObject.UnBind();

        RendererObject.Bind();

        int j{0};

        for(int j = 0 ; j <50 ; j++)
        {
            auto start = high_resolution_clock::now();
            auto TextureObject=std::make_shared<Texture>(image);
            TextureObject->Bind();

            RendererObject.SetUniformli(RotateImageOperation);
            RendererObject.Draw(); 

            std::shared_ptr<cv::Mat> gl_out = std::make_shared<cv::Mat>(image.rows, image.cols, CV_8UC3);

            glReadBuffer(GL_COLOR_ATTACHMENT0);
            glReadPixels(0, 0, image.cols, image.rows,
                        GL_BGR, GL_UNSIGNED_BYTE,
                        gl_out->data);
            flip(*gl_out,*gl_out,0);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            std::cout << duration.count() << std::endl;
        }
    
        i++;

    glfwTerminate();
    }
    return 0;
}