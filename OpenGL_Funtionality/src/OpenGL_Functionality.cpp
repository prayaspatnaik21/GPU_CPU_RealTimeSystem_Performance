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
            "Edge Detector Shader 3"<<std::endl;

    int chooseShader{0};
    std::cin >> chooseShader;

    std::string shaderPath  = " ";

    switch(chooseShader)
    {
        case 1:
            shaderPath = "../resources/shaders/shaderGrey.shader";
            break;
        case 2:
            shaderPath = "../resources/shaders/shaderGaussian.shader";
            break;
        case 3:
            shaderPath = "../resources/shaders/shaderEdgeDetector.shader";
            break;
        default:
            shaderPath = "../resources/shaders/shaders.shader"; 
    }

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    if(!glewInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */

    Mat image = imread("../resources/Images/Sam_0.jpg",1);
    //flip(image,image,0);
    std::cout << "Image Resolution" << " " << image.cols << "X" << image.rows << std::endl;
	

    window = glfwCreateWindow(image.cols, image.rows, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    //Setting glewExperimental to true ensures GLEW uses more modern techniques for managing OpenGL functionality
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    /*we want to render a single triangle we want to specify a total of three vertices with
    each vertex having a 3D position. */

    unsigned int indices[] = { 
        0,1,3,
        1,2,3
    };

    Transformation Transform;

    glm::mat4 RotationMatrix = Transform.GetRotationMatrix(90.0f);
    
    auto start = high_resolution_clock::now();
    Renderer RendererObject(shaderPath,RotationMatrix);
    RendererObject.AddBuffer();
    RendererObject.UnBind();

    RendererObject.Bind();

    auto TextureObject=std::make_shared<Texture>(image);
    
    //TextureObject->UnBind();
    TextureObject->Bind();

    RendererObject.SetUniformli();
    RendererObject.Draw();
        /* Loop until the user  closes the window */
    /*The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW
    has been instructed to close, if so, the function returns true and the game loop stops     running, after which we can close the application */
    std::shared_ptr<cv::Mat> gl_out = std::make_shared<cv::Mat>(image.rows, image.cols, CV_8UC3);

    glReadBuffer(GL_COLOR_ATTACHMENT0);
   
    glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, gl_out->data);
    // auto stop = high_resolution_clock::now();
	// auto duration = duration_cast<microseconds>(stop - start);

	// std::cout << "Time taken by function: "
    //      << duration.count() << " microseconds" << std::endl;
    //flip(*gl_out,*gl_out,0);
    cv::imshow(" image1", *gl_out);
    cv::waitKey(0);

    // glClear(GL_COLOR_BUFFER_BIT);
    // RendererObject.Draw();
    // glfwSwapBuffers(window);
    // glfwPollEvents(); 


       /* Loop until the user  closes the window */
    /*The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW
    has been instructed to close, if so, the function returns true and the game loop stops     running, after which we can close the application */
    while (!glfwWindowShouldClose(window))
    {
         /* Render here */
         glClear(GL_COLOR_BUFFER_BIT);
         RendererObject.Draw();

    //     //Use when we don't use Index Buffer and this will use that buffer which is binded
       

    //     /*The glfwSwapBuffers will swap the color buffer (a large buffer that contains color values for each pixel in GLFW’s window) that has been used to draw in duri ng this iteration and show it as output to the screen*/
         glfwSwapBuffers(window);

    //     /*The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events) and calls the corresponding functions (which we can set via callback methods)*/
         glfwPollEvents(); 
     }

    //glDeleteProgram(shader);

    /* This will clean up all the resources and properly exit the application. */
    glfwTerminate();
    return 0;
}