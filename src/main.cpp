#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

GLint g_WindowSizeX = 640;
GLint g_WindowSizeY = 480;
void glfwWindowSizeCallback(GLFWwindow* pWindow, GLint width, GLint height);
void glfwKeyCallback(GLFWwindow* pWindow, GLint key, GLint scancode, GLint action, GLint mode);

int main(void)
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(g_WindowSizeX, g_WindowSizeY, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	if(!gladLoadGL())
	{
		std::cout<<"Can't load GLAD!"<<std::endl;
		return -1;
	}
    std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(1,1,0,1);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void glfwWindowSizeCallback(GLFWwindow* pWindow, GLint width, GLint height)
{
    g_WindowSizeX = width;
    g_WindowSizeY = height;
    glViewport(0, 0, g_WindowSizeX, g_WindowSizeY);
    
}

void glfwKeyCallback(GLFWwindow* pWindow, GLint key, GLint scancode, GLint action, GLint mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
   
}