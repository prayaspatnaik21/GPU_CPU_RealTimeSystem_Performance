// #include <GL/glew.h>
// #include <GLFW/glfw3.h> 
// #include <opencv2/opencv.hpp>
// #include <malloc.h>
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>
#include "Headers.h"
#include "Renderer.h"
// #include "Texture.h"
//#include "VertexBuffer.h"
// #include "VertexArray.h"
// #include "IndexBuffer.h"
// #include "Shader.h"

using namespace cv;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    if(!glewInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

    Mat image = imread("../resources/Images/Sam_1.jpg",1);
    flip(image,image,0);
	Size outDim = image.size();

    std::string shaderPath = "../resources/shaders/shaders.shader";

    Renderer RendererObject(image,shaderPath);
    RendererObject.AddBuffer();
    RendererObject.UnBind();

    /* Loop until the user  closes the window */
    /*The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW
    has been instructed to close, if so, the function returns true and the game loop stops     running, after which we can close the application */
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        RendererObject.Bind();
        RendererObject.Draw();

        //Use when we don't use Index Buffer and this will use that buffer which is binded
       

        /*The glfwSwapBuffers will swap the color buffer (a large buffer that contains color values for each pixel in GLFW’s window) that has been used to draw in duri ng this iteration and show it as output to the screen*/
        glfwSwapBuffers(window);

        /*The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events) and calls the corresponding functions (which we can set via callback methods)*/
        glfwPollEvents(); 
    }

    //glDeleteProgram(shader);

    /* This will clean up all the resources and properly exit the application. */
    glfwTerminate();
    return 0;
}