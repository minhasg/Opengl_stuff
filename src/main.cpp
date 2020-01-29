#define GLFW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>

#include "Triangle.h"
#include "Rectangle.h"
#include "Shader.h"

#include <iostream>
#include <cmath>

void printOpenGLInfo()
{
    std::cout << "Printing OpenGL information:\n";
    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

int main()
{
    std::cout << "Initializing glfw\n";
	if(!glfwInit())
	{
        std::cout << "Failed to initialize GLFW!\n";
		return -1;
	}
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hurh", NULL, NULL);
	glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW!\n";
        return -2;
    }
    
    printOpenGLInfo();
    Triangle tri;
    tri.bindShader("shaders/BasicTriangle");
    Rectangle rect;
    float time = 0;
    
    std::cout << "Entering main loop.\n";
	while(!glfwWindowShouldClose(window))
	{   	
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Get time value
        time = glfwGetTime();
        time = 0.5f * std::sin(time) + 0.5f;
        tri.getShader().setUniform("time", time); 

        // Draw everything
        //std::cout << "Drawing triangle.\n";
        tri.draw();
        //rect.draw();        

        // Swap buffers
        //std::cout << "Swapping buffers.\n";
		glfwSwapBuffers(window);
        
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;

}
