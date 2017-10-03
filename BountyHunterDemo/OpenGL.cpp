#include "OpenGL.h"

#include <stdio.h>

void  __glGetLastErrorImpl(const char* file, int line, const char *func) {

	GLenum err = glGetError();

	while (err != GL_NO_ERROR) {

		switch (err) {

			case GL_INVALID_OPERATION:      
				fprintf(stderr, "%s:%d @%s [%s] \n", file, line, func, "OpenGL error GL_INVALID_OPERATION."); break;

			case GL_INVALID_ENUM:
				fprintf(stderr, "%s:%d @%s [%s] \n",file, line, func, "OpenGL error GL_INVALID_ENUM."); break;

			case GL_INVALID_VALUE:
				fprintf(stderr, "%s:%d @%s [%s] \n",file, line, func, "OpenGL error GL_INVALID_VALUE."); break;

			case GL_OUT_OF_MEMORY:
				fprintf(stderr, "%s:%d @%s [%s] \n",file, line, func, "OpenGL error GL_OUT_OF_MEMORY."); break;

			default:
				fprintf(stderr, "%s:%d @%s [%s] \n",file, line, func, "OpenGL error unknown."); break;
		}

		// Check for other errors, if any
		err = glGetError();
	}
}