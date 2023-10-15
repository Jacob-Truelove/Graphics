#include "ShaderClass.h"


std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);

	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}

Shader::Shader(const char* vertextFile, const char* fragFile) {
	std::string vertexCode = get_file_contents(vertextFile);
	std::string fragCode = get_file_contents(fragFile);

	const char* vertexSource = vertexCode.c_str();
	const char* FragSource = fragCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Opens vertexShader to have its source code changed, as well as the number elements 
	// the address of the shader and an array of string lengths
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compiles the source code of vertexShader and stores it in its object state
	glCompileShader(vertexShader);

	// Create a GLuint that sets fragment shader as its type The other lines do the same thing
	// as with vertext shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragSource, NULL);
	glCompileShader(fragmentShader);

	// Creates a program that shader objects can be attached to
	ID = glCreateProgram();

	// Attaches the shaders made to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Links the attached shaders so they may be compiled into an executable
	glLinkProgram(ID);

	// Deletes the shaders to free space
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}