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

using VertexArrayID = GLuint;

struct VertexArray
{
	VertexArrayID	m_ID;

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

	inline void Bind() const
	{
		glBindVertexArray(this->m_ID);
	}

	inline void Unbind() const
	{
		glBindVertexArray(0);
	}

	inline const VertexArrayID GetID() const { return this->m_ID; }
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

using VertexBufferID = GLuint;

struct VertexBuffer
{
	VertexBufferID		m_ID;

	const GLsizeiptr	m_BufferCapacity;
	GLintptr 			m_CurrentBufferIndex;

	VertexBuffer(const GLsizeiptr size) :
		m_BufferCapacity(size),
		m_CurrentBufferIndex(0)
	{
		glGenBuffers(1, &this->m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);

		glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGetLastError();
	}

	~VertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &this->m_ID);

		glGetLastError();
	}

	inline void Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
	}

	inline void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	inline const VertexBufferID GetID() const { return this->m_ID; }

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

	GLintptr BufferVertexData(const void* data, GLsizeiptr size)
	{
		assert(this->m_CurrentBufferIndex + size < this->m_BufferCapacity && "VertexBuffer capacity exceeded.");

		GLintptr dataBufferIndex = this->m_CurrentBufferIndex;

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

using IndexBufferID = GLuint;

struct IndexBuffer
{
	IndexBufferID		m_ID;

	const GLsizeiptr	m_BufferCapacity;
	GLintptr			m_CurrentBufferIndex;

	IndexBuffer(const GLsizeiptr size) :
		m_BufferCapacity(size),
		m_CurrentBufferIndex(0)
	{
		glGenBuffers(1, &this->m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glGetLastError();
	}

	~IndexBuffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &this->m_ID);

		glGetLastError();
	}

	inline void Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);
	}

	inline void Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	inline const IndexBufferID GetID() const { return this->m_ID; }


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

	GLintptr BufferIndexData(const void* data, GLsizeiptr size)
	{
		assert(this->m_CurrentBufferIndex + size < this->m_BufferCapacity && "IndexBuffer capacity exceeded.");

		GLintptr dataBufferIndex = this->m_CurrentBufferIndex;

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, this->m_CurrentBufferIndex, size, data);
		glGetLastError();

		this->m_CurrentBufferIndex += size;

		return dataBufferIndex;
	}
};

#endif // __GL_BUFFERS_H__