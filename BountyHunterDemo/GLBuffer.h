///-------------------------------------------------------------------------------------------------
/// File:	GLBuffer.h.
///
/// Summary:	Declares a few auxillary classes for handling OpenGL buffer objects.
///-------------------------------------------------------------------------------------------------


#ifndef __GL_BUFFERS_H__
#define __GL_BUFFERS_H__

#define BUFFER_OFFSET(x) (const GLvoid*)(x)


#include <assert.h>

#include "OpenGL.h"




///-------------------------------------------------------------------------------------------------
/// Struct:	VertexArray
///
/// Summary:	Auxillary class for Vertex Arrays objects.
///
/// Author:	Tobias Stein
///
/// Date:	7/10/2017
///-------------------------------------------------------------------------------------------------

struct VertexArray
{
	GLuint			m_ID;

	VertexArray()
	{
		glGenVertexArrays(1, &this->m_ID);
		glBindVertexArray(this->m_ID);
		glBindVertexArray(0);

		glGetLastError();
	}

	~VertexArray()
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &this->m_ID);

		glGetLastError();
	}

	inline void Bind()
	{
		glBindVertexArray(this->m_ID);
	}

	inline void Unbind()
	{
		glBindVertexArray(0);
	}
};

///-------------------------------------------------------------------------------------------------
/// Struct:	VertexBuffer
///
/// Summary:	Auxillary class for Vertex Buffer Arrays.
///
/// Author:	Tobias Stein
///
/// Date:	7/10/2017
///-------------------------------------------------------------------------------------------------

struct VertexBuffer
{
	GLuint			m_ID;

	const size_t	m_BufferCapacity;
	size_t			m_CurrentBufferIndex;

	VertexBuffer(const size_t size) :
		m_BufferCapacity(size),
		m_CurrentBufferIndex(0)
	{
		glGenBuffers(1, &this->m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);

		glGetLastError();
	}

	~VertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &this->m_ID);

		glGetLastError();
	}

	inline void Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
	}

	inline void Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	///-------------------------------------------------------------------------------------------------
	/// Fn:	size_t BufferVertexData(const void* data, size_t size)
	///
	/// Summary:	Stores new data in vertex buffer and returns an index to first data location in buffer.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	7/10/2017
	///
	/// Parameters:
	/// data - 	   	The data.
	/// size - 	   	The size.
	///
	/// Returns:	A size_t.
	///-------------------------------------------------------------------------------------------------

	size_t BufferVertexData(const void* data, size_t size)
	{
		assert(this->m_CurrentBufferIndex + size < this->m_BufferCapacity && "VertexBuffer capacity exceeded.");

		size_t dataBufferIndex = this->m_CurrentBufferIndex;

		glBufferSubData(GL_ARRAY_BUFFER, this->m_CurrentBufferIndex, size, data);
		glGetLastError();

		this->m_CurrentBufferIndex += size;

		return dataBufferIndex;
	}
};

///-------------------------------------------------------------------------------------------------
/// Struct:	IndexBuffer
///
/// Summary:	Auxillary class for Index Buffer Arrays.
///
/// Author:	Tobias Stein
///
/// Date:	7/10/2017
///-------------------------------------------------------------------------------------------------

struct IndexBuffer
{
	GLuint			m_ID;

	const size_t	m_BufferCapacity;
	size_t			m_CurrentBufferIndex;

	IndexBuffer(const size_t size) :
		m_BufferCapacity(size),
		m_CurrentBufferIndex(0)
	{
		glGenBuffers(1, &this->m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);

		glGetLastError();
	}

	~IndexBuffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &this->m_ID);

		glGetLastError();
	}

	inline void Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);
	}

	inline void Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	///-------------------------------------------------------------------------------------------------
	/// Fn:	size_t BufferIndexData(const void* data, size_t size)
	///
	/// Summary:	Stores new index data in index buffer and returns an index to first data location in buffer.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	7/10/2017
	///
	/// Parameters:
	/// data - 	   	The data.
	/// size - 	   	The size.
	///
	/// Returns:	A size_t.
	///-------------------------------------------------------------------------------------------------

	size_t BufferIndexData(const void* data, size_t size)
	{
		assert(this->m_CurrentBufferIndex + size < this->m_BufferCapacity && "IndexBuffer capacity exceeded.");

		size_t dataBufferIndex = this->m_CurrentBufferIndex;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, this->m_CurrentBufferIndex, size, data);
		glGetLastError();

		this->m_CurrentBufferIndex += size;

		return dataBufferIndex;
	}
};

#endif // __GL_BUFFERS_H__