#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
	public:
		GLuint ID;
		EBO(GLuint* indicies, GLsizeiptr size);

		void Bind();
		void unBind();
		void Delete();
};
#endif // !EBO_CLASS_H
