#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <opencv2/opencv.hpp>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

//VertexArray are a way to bind vertex buffer with a certain specification of layout of that actual vertex buffer

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

    ///Testing Class Implementation
    //Renderer render(6,path);
    //VertexArray vao;
    //VertexBuffer vb(4*2*sizeof(float));
    //IndexBuffer  ib(6);
    string path{"../resources/shaders/shaders.shader"};
    Renderer render(6,path);
    //Shader shd(path);
    //shd.Bind();
    render.UnBind();

    //vao.AddBuffer();

    //UnBinding VertexArrayObject, Program Object,BufferData
    // vao.UnBind();
    // shd.UnBind();

    //int location = shd.GetUniformLocation("u_Color");
    
    float r = 0.0f; 
    float g = 0.0f; 
    float b = 0.0f; 
    float increament = 0.25f;

    /* Loop until the user  closes the window */
    /*The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW
    has been instructed to close, if so, the function returns true and the game loop stops     running, after which we can close the application */
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        render.Bind();
        //shd.Bind();
        shd.SetUniformLocation(location,r,g,b);
        //vao.Bind();
        //ib.Bind();
        
        //Use when we don't use Index Buffer and this will use that buffer which is binded
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);
        render.Draw();

        if(r > 1.0f)
            increament = -0.05f;
        else if(r < 0.0f)
            increament = 0.05f;
        
        r+=increament;
        g+=increament;
        b+=increament;

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