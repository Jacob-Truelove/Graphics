#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO VBO, GLuint Layout) {
	VBO.Bind();
	glVertexAttribPointer(Layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(Layout);
	VBO.unBind();
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::unBind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}