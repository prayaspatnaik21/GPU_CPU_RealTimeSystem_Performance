# GPU_CPU_RealTimeSystems_Performance

## OpenGL Set Up : Installing Dependencies

    1. sudo apt-get update
    2. sudo apt-get install cmake pkg-config
    3. sudo apt-get install mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev
    4. sudo apt-get install libglew-dev libglfw3-dev libglm-dev
    5. sudo apt-get install libao-dev libmpg123-dev

## OpenGL Setup : GLFW Library

    1. cd /usr/local/lib/
    2. git clone https://github.com/glfw/glfw.git
    3. cd glfw
    4. cmake .
    5. make
    6. sudo make install

## OpenGL Setup: GLAD Library

    1.[WebService](https://glad.dav1d.de)
    2.Set the Language to C++ and Choose OpenGL Specifications.
    3.Select gl API version of atleast 3.3 and set the profile to Core.
    4.Check that the Generate a loader option is selected.
    5.Click Generate to produce the resulting library files.
    5.Download the glad.zip file.
    6.Copy the folders inside the include folder into system include directory.(cp -R include/* /usr/include/)
    7.Copy the glad.c inside your src folder of your current direcotry or to your current working directory.

## OpenGL Set up: GLEW Library

    1. cd /usr/local/lib/
    2. git clone https://github.com/nigels-com/glew.git

## Command to run the OpenGL Program

    g++ OpenGLFuntionality.cpp -o hw_opengl -lGL -lGLEW -lGLU -lglut -lglfw -ldl

## References

    1.[Khronos](https://www.khronos.org/registry/OpenGL/index_gl.php)
    2.[OpenGL Docs](https://docs.gl/#)
