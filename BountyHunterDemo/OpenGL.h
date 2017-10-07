#ifndef __OPEN_GL_H__
#define __OPEN_GL_H__

#define WIN32_LEAN_AND_MEAN
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
#ifdef _DEBUG
#define glGetLastError() __glGetLastErrorImpl( __FILE__, __LINE__, __FUNCTION__ )
#else
#define glGetLastError()
#endif



typedef GLfloat		VertexPositionData;
typedef GLushort	VertexIndexData;
typedef GLfloat		VertexNormalData;
typedef GLfloat		VertexTexCoordData;
typedef GLfloat		VertexColorData;

static constexpr GLenum VERTEX_POSITION_DATA_TYPE			{ GL_FLOAT };
static constexpr GLenum VERTEX_INDEX_DATA_TYPE				{ GL_UNSIGNED_SHORT };
static constexpr GLenum VERTEX_NORMAL_DATA_TYPE				{ GL_FLOAT };
static constexpr GLenum VERTEX_TEXCOORD_DATA_TYPE			{ GL_FLOAT };
static constexpr GLenum VERTEX_COLOR_DATA_TYPE				{ GL_FLOAT };

static constexpr size_t VERTEX_POSITION_DATA_ELEMENT_LEN	{ 3 };
static constexpr size_t VERTEX_INDEX_DATA_ELEMENT_LEN		{ 1 };
static constexpr size_t VERTEX_NORMAL_DATA_ELEMENT_LEN		{ 3 };
static constexpr size_t VERTEX_TEXCOORD_DATA_ELEMENT_LEN	{ 2 };
static constexpr size_t VERTEX_COLOR_DATA_ELEMENT_LEN		{ 3 };

static constexpr size_t VERTEX_POSITION_DATA_ELEMENT_SIZE	{ VERTEX_POSITION_DATA_ELEMENT_LEN * sizeof(VertexPositionData) };
static constexpr size_t VERTEX_INDEX_DATA_ELEMENT_SIZE		{ VERTEX_INDEX_DATA_ELEMENT_LEN * sizeof(VertexIndexData) };
static constexpr size_t VERTEX_NORMAL_DATA_ELEMENT_SIZE		{ VERTEX_NORMAL_DATA_ELEMENT_LEN * sizeof(VertexNormalData) };
static constexpr size_t VERTEX_TEXCOORD_DATA_ELEMENT_SIZE	{ VERTEX_TEXCOORD_DATA_ELEMENT_LEN * sizeof(VertexTexCoordData) };
static constexpr size_t VERTEX_COLOR_DATA_ELEMENT_SIZE		{ VERTEX_COLOR_DATA_ELEMENT_LEN * sizeof(VertexColorData) };

#endif // __OPEN_GL_H__