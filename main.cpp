#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// The strings that tell the vertexes their positions relative to one another
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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
	GLfloat vertices[] = {-.5f, -.5f * float(sqrt(3))/3, 0.0f,
	.5f, -.5f * float(sqrt(3)) / 3, 0.0f, 
	0.0f, 0.5f * float(sqrt(3))* 2/3, 0.0f };

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

	// Create a vertex shader and establish its shader type with glCreatShader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Opens vertexShader to have its source code changed, as well as the number elements 
	// the address of the shader and an array of string lengths
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compiles the source code of vertexShader and stores it in its object state
	glCompileShader(vertexShader);

	// Create a GLuint that sets fragment shader as its type The other lines do the same thing
	// as with vertext shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Creates a program that shader objects can be attached to
	GLuint shaderProgram = glCreateProgram();

	// Attaches the shaders made to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Links the attached shaders so they may be compiled into an executable
	glLinkProgram(shaderProgram);

	// Deletes the shaders to free space
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Always generate VAO first
	GLuint VAO, VBO;

	// Changes VAO's with the listed number of vertext arrays inside
	glGenVertexArrays(1, &VAO);
	// Changes the VBO object with the number of objects listed
	glGenBuffers(1, &VBO);

	// Binds the generted objects with the shaders
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Gives the newly binded object memory to use
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Defines the vertex shader's attribute data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Enables attributes presumably
	glEnableVertexAttribArray(0);

	// Now that the vertexes are compiled we unbined them to free the data
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Establishes the color of glad and confines it to the buffer
	glClearColor(0.07f, 0.13f, 0.17f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	// Swaps glfw's buffer to the new one created with glad
	glfwSwapBuffers(window);

	// Makes sure that the program doesn't end until the window is closed
	while (!glfwWindowShouldClose(window)) {
		// makes sure the program runs along with the window
		glClearColor(0.07f, 0.13f, 0.17f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window); 

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Frees the space window was taking preventing memory leaks and terminating glfw
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}