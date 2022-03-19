#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//VertexArray are a way to bind vertex buffer with a certain specification of layout of that actual vertex buffer

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

struct ShaderProgramSource ReadShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    enum class ShaderType
    {
        NONE = -1,VERTEX = 0,FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else{
            ss[(int)type]  << line << "\n";

        }
    }

    return { ss[0].str(),ss[1].str()};
}
/*Dynamically compile it at run-time from its source code*/
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

    glfwSwapInterval(1);

    //Setting glewExperimental to true ensures GLEW uses more modern techniques for managing OpenGL functionality
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    /*we want to render a single triangle we want to specify a total of three vertices with
    each vertex having a 3D position. */
    float positions[] = {

        -0.5f,-0.5f,
        0.5f,-0.5f,
        0.5f,0.5f,
        -0.5f,0.5f, 
    }; 

    unsigned int indices[] = { 
        0,1,2,
        2,3,0
    };

    //VertexArray are a way to bind vertex buffer with a certain specification of layout of that actual vertex buffer
    unsigned int vao;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    /*glBufferData is a function specifically targeted to copy user-defined data into the currently
    bound buffer. */
    unsigned int buffer;
    //Generate the buffer
    glGenBuffers(1,&buffer);
    //Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    //Static or Dynamic it's upto the type of the Application
    glBufferData(GL_ARRAY_BUFFER,6*2*sizeof(float),positions,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    //Location should be the index of the vertex attrib pointer
    //Inedx 0 of this vertex array is bound to currently bound gl array buffer
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);

    unsigned int ibo;
    //Generate the buffer
    glGenBuffers(1,&ibo);
    //Bind the buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
    //Static or Dynamic it's upto the type of the Application
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,4*2*sizeof(unsigned int),indices,GL_STATIC_DRAW);


    ShaderProgramSource source = ReadShader("resources/shaders/shaders.shader");
    
    
    unsigned int shader = CreateShader(source.VertexSource,source.FragmentSource);
    glUseProgram(shader);

    //UnBinding VertexArrayObject, Program Object,BufferData
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);


    int location = glGetUniformLocation(shader,"u_Color");

    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

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

        glUseProgram(shader);
        glUniform4f(location,r,g,b,0.0f);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
        
        //Use when we don't use Index Buffer and this will use that buffer which is binded
        //glDrawArrays(GL_TRIANGLES,0,6);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);

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

    glDeleteProgram(shader);

    /* This will clean up all the resources and properly exit the application. */
    glfwTerminate();
    return 0;
}