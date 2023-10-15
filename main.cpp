#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


// The strings that tell the vertexes their positions relative to one another
//Fragment Shader source code

int main() {
	// initializes glfw
	glfwInit();

	// this is telling the code what version of glfw we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// tells glfw that we are specifically using the core version of it
	// so we only have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// The vertice locations in the order of lower left corner lower right corner, then upper corner
	//initializes a glfw window(must be a pointer like how FILE must always be on)
	GLFWwindow* window = glfwCreateWindow(800, 800, "Graphics", NULL, NULL);


	// This just checks if a window actually exists
	if (window == NULL) {
		std::cout << "window failed to open" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Tells glfw that window is the context in which it acts in
	glfwMakeContextCurrent(window);

	// Loads glad into the graphical interface and specifies its influence
	// Size is in terms of pixels
	gladLoadGL();
	// Specifies the viewport of openGL
	glViewport(0, 0, 800, 800);

GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 1, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	Shader shaderprogram("default.vert", "default.frag");
	
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.unBind();
	VBO1.unBind();
	EBO1.unBind();
	
	// Swaps glfw's buffer to the new one created with glad
	glfwSwapBuffers(window);

	// Makes sure that the program doesn't end until the window is closed
	while (!glfwWindowShouldClose(window)) {
		// makes sure the program runs along with the window
		glClearColor(0.07f, 0.13f, 0.17f, 1.0);

		glClear(GL_COLOR_BUFFER_BIT);

		shaderprogram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window); 

		glfwPollEvents();
	}

	shaderprogram.Delete();

	// Frees the space window was taking preventing memory leaks and terminating glfw
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}