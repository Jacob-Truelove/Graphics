#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
	GLuint ID;

	VAO();

	void LinkVBO(VBO VBO, GLuint Layout);
	void Bind();
	void unBind();
	void Delete();
};
#endif // !VBO_H
