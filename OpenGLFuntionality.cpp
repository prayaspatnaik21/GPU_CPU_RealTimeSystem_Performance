#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include <iostream>

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

    if(glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[6] = {

            -0.5f,-0.5f,
            0.0f,0.5f,
            0.5f,-0.5f
        
        };

    unsigned int buffer;
    //Generate the buffer
    glGenBuffers(1,&buffer);
    //Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    //Static or Dynamic it's upto the type of the Application
    glBufferData(GL_ARRAY_BUFFER,6*sizeof(float),positions,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);

    /* Loop until the user  closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Use when we don't use Index Buffer and this will use that buffer which is binded
        glDrawArrays(GL_TRIANGLES,0,3);

        /* Swap fr ont and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents(); 
    }

    glfwTerminate();
    return 0;
}