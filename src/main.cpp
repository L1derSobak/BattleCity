/*
	       ╔══════════════════════════════════╗
	       ║	   CREATED BY L1derSobak      ║  
	       ║   Date of creating: Aug 11, 2021 ║ 
           ╚══════════════════════════════════╝
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"

#include <iostream>

//Cords of triangle's vertex
GLfloat point[] = { 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f };
//RGB color of triangle's vertex
GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
//Coords of triangle's vertexes for texture
GLfloat textureCoords[] = { 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f };

//default Width and height of window
GLint windowSizeX = 640;
GLint windowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, GLint width, GLint height);
void glfwKeyCallback(GLFWwindow* pWindow, GLint key, GLint scancode, GLint action, GLint mode);
void prepareShaders(GLuint &vao);

int main(int argc, char** argv)
{
	GLFWwindow* window;

	// Initialize the library                                        
	if (!glfwInit())
		return -1;

	// Create a windowed mode window and its OpenGL context 
	window = glfwCreateWindow(windowSizeX, windowSizeY, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//Bind callbacks to our functions
	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
	glfwSetKeyCallback(window, glfwKeyCallback);

	// Make the window's context current 
	glfwMakeContextCurrent(window);

	//Initial the GLAB library
	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}

	//Just some test of library
	std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	//Set background color
	glClearColor(1, 1, 0, 1);

	//Creating resource maanger
	ResourceManager resourceManager(argv[0]);
	//Create and init of shader program
	auto defaultShaderProgram = resourceManager.loadShaders("DefaultShader", "shaders/vertex.txt", "shaders/fragment.txt");
	if (!defaultShaderProgram)
	{
		std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
		return -1;
	}
		
	auto tex = resourceManager.loadTexture("DefaultTexture", "textures/texture.png");
	
	//Creating ID for vertex array object
	GLuint vertexArrayObject = 0;
	prepareShaders(vertexArrayObject);
	
	GLuint texCoordsVbo = 0;
	glGenBuffers(1, &texCoordsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordsVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordsVbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	defaultShaderProgram->use();
	defaultShaderProgram->setInt("tex", 0);

	// Loop until the user closes the window 
	while (!glfwWindowShouldClose(window))
	{
		// Render here 
		glClear(GL_COLOR_BUFFER_BIT);

		//Use our sahder program and draw triangle
		defaultShaderProgram->use();
		glBindVertexArray(vertexArrayObject);
		tex->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap front and back buffers 
		glfwSwapBuffers(window);

		// Poll for and process events 
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void glfwWindowSizeCallback(GLFWwindow* pWindow, GLint width, GLint height)
{
	windowSizeX = width;
	windowSizeY = height;
	glViewport(0, 0, windowSizeX, windowSizeY);

}

void glfwKeyCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

}

void prepareShaders(GLuint& vao)
{
	//Creating vertex buffer object of triangle point's coords
	GLuint pointsVertexBufferObject = 0;
	glGenBuffers(1, &pointsVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, pointsVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

	//Creating vertex buffer object of triangle point's color
	GLuint colorsVbo = 0;
	glGenBuffers(1, &colorsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	//Generating and bind of vertex array object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//apply our shaders:
	//points
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pointsVertexBufferObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	//colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

