#ifndef __OPEN_GL_H__
#define __OPEN_GL_H__

#include <Windows.h>

#include <GL/glew.h>


#include <GL/GL.h>
#include <GL/GLU.h>

/** __glGetLastErrorImpl
	This method implements a mechanism that checks the last OpenGL errors 
	that occured since the last time this.
*/
void __glGetLastErrorImpl(const char* file, int line, const char *func);

/** glGetLastError
	This is a convinient macro which invokes the implementation of glCheckError
	with the right file name and line number.
*/
#ifdef DEBUG_MODE
#define glGetLastError() __glGetLastErrorImpl( __FILE__, __LINE__, __FUNCTION__ )
#else
#define glGetLastError()
#endif


#endif // __OPEN_GL_H__