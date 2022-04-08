#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <opencv2/opencv.hpp>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

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
    float positions[] = {

        0.5f,0.5f,0.0f,1.0f,1.0f,
        0.5f,-0.5f,0.0f, 1.0f,0.0f,
        -0.5f,-0.5f,0.0f,0.0f,0.0f,
        -0.5f,0.5f,0.0f, 0.0f,1.0f
    }; 

    unsigned int indices[] = { 
        0,1,3,
        1,2,3
    };

    Mat image = imread("../resources/Images/Sam_1.jpg",1);
    flip(image,image,0);
	Size outDim = image.size();

    std::cout << outDim << std::endl;

    //VertexArray are a way to bind vertex buffer with a certain specification of layout of that actual vertex buffer
    unsigned int vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    ///Testing Class Implementation
    VertexBuffer vb(positions,5*4*sizeof(float));
    IndexBuffer  ib(indices,6);
    Shader shd("../resources/shaders/shaders.shader");
    shd.Bind();

    Texture tex(image);
    shd.SetUniform1i("u_Texture",0);

    glEnableVertexAttribArray(0);
    //Location should be the index of the vertex attrib pointer
    //Inedx 0 of this vertex array is bound to currently bound gl array buffer
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(3*sizeof(float)));


    //UnBinding VertexArrayObject, Program Object,BufferData
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    int location = shd.GetUniformLocation("u_Color");
    shd.UnBind();
    vb.UnBind();

    /* Loop until the user  closes the window */
    /*The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW
    has been instructed to close, if so, the function returns true and the game loop stops     running, after which we can close the application */
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        tex.Bind(0);
        shd.Bind();
        //shd.SetUniformLocation(location,r,g,b);
        //glUniform4f(location,0.2,1.0,1.0,0.0f);
        glBindVertexArray(vao);
        ib.Bind();
        
        //Use when we don't use Index Buffer and this will use that buffer which is binded
        //glDrawArrays(GL_TRIANGLES,0,6);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);

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