# SPECIFY THE MINIMUM VERSION OF CMAKE REQUIRED
cmake_minimum_required(VERSION 2.8.12)


# SPECIFY YOUR PROJECT NAME
PROJECT(OpenGL_Functionality)


# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

### Uncomment the line below and specify the path to OpenCV directory i.e. the path to the OpenCVConfig.cmake file. Check the examples given below.
###SET PATH TO OPENCV CMAKE CONFIG FILES

SET(OpenCV_DIR /Home/home/installation/OpenCV/lib/cmake/opencv4)

################### OpenCV_DIR Examples  #####################
#
### MACOS : /Users/<Username>/installation/OpenCV/lib/cmake/opencv4
### UBUNTU : /usr/local/share/OpenCV/
#
##############################################################

set(OpenGL_GL_PREFERENCE "GLVND")


# MAKE SURE OPENCV IS INSTALLED CORRECTLY
find_package( OpenCV REQUIRED )
find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED )

add_library(GLAD  "resources/glad.c")
set(LIBS    glfw    ${OPENGL_LIBRARY}   GLAD    ${OpenCV_LIBS} ${GLEW_LIBRARIES})

SET(PROJECT_DEPS "/usr/local/include")
SET(glew_inc "${PROJECT_DEPS}/glew/include/GL/")
SET(glew_src "${PROJECT_DEPS}/glew/src/")
SET(glfw_inc "${PROJECT_DEPS}/glfw/include/GLFW/")
SET(glfw_src "${PROJECT_DEPS}/glfw/src/")

# INCLUDE OPENCV DIRECTORIES
include_directories( ${OpenCV_INCLUDE_DIRS} ${glew_inc} ${glew_src} ${glfw_inc} ${glfw_src})

set(SOURCES src/OpenGL_Functionality.cpp src/Renderer.cpp src/Renderer.h src/VertexBuffer.cpp src/VertexBuffer.h src/IndexBuffer.cpp src/IndexBuffer.h src/Shader.cpp src/Shader.h src/Texture.cpp src/Texture.h src/VertexArray.cpp src/VertexArray.h src/Headers.h src/Renderer.cpp src/Renderer.h)

# MACRO TO COMPILE CPP FILES
# Do Not Edits

ADD_EXECUTABLE(OpenGL_Functionality ${SOURCES})
TARGET_LINK_LIBRARIES(OpenGL_Functionality ${LIBS} )


# COMPILE CPP FILES USING THIS LINE
######## EDIT THE FILE NAMES ########
#add_example(OpenGL_Functionality)
#add_example(sampleCode2) and so on