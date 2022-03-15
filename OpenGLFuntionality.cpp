#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <malloc.h>
#include <iostream>

static unsigned int CompileShader(unsigned int type,const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE){
        int length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)malloc(length * sizeof(char)); // stack Dynamically
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile" << " " <<
                    (type == GL_VERTEX_SHADER ? "vertex":"fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vertexShaderID = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);


    glAttachShader(program, vertexShaderID);
    glAttachShader(program, fragmentShaderID);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return program;
}

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

    //Setting glewExperimental to true ensures GLEW uses more modern techniques for managing OpenGL functionality
    glewExperimental = GL_TRUE;

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

    //Location should be the index of the vertex attrib pointer
    std::string vertexShader = 
                "#version 330 core\n"
                "\n"
                "layout(location = 0) in vec4 positions;\n"
                "void main()\n"
                "{\n"
                " gl_Position = positions;\n"
                "}\n";

    std::string fragmentShader = 
            "#version 330 core\n"
            "\n"
            "layout(location = 0) out vec4 color;\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0,0.0,0.0,1.0);\n"
            "}\n";
    unsigned int shader = CreateShader(vertexShader,fragmentShader);
    glUseProgram(shader);

    /* Loop until the user  closes the window */
    /*The glfwWindowShouldClose function checks at the start of each loop iteration if GLFW
    has been instructed to close, if so, the function returns true and the game loop stops     running, after which we can close the application */
    
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        //Use when we don't use Index Buffer and this will use that buffer which is binded
        glDrawArrays(GL_TRIANGLES,0,3);

        /*The glfwSwapBuffers will swap the color buffer (a large buffer that contains color values for each pixel in GLFW’s window) that has been used to draw in during this iteration and show it as output to the screen*/
        glfwSwapBuffers(window);

        /*The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events) and calls the corresponding functions (which we can set via callback methods)*/
        glfwPollEvents(); 
    }

    glDeleteProgram(shader);

    /* This will clean up all the resources and properly exit the application. */
    glfwTerminate();
    return 0;
}