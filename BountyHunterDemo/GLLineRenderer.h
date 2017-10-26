///-------------------------------------------------------------------------------------------------
/// File:	GLLineRenderer.h.
///
/// Summary:	Declares the gl line renderer class.
///-------------------------------------------------------------------------------------------------

#ifndef __GL_LINE_RENDERER_H__
#define __GL_LINE_RENDERER_H__

#include "Material.h"
#include "GLBuffer.h"

class GLLineRenderer
{
	static constexpr size_t		MAX_LINES { 2 * 512 };

private:

	Material					m_LineMaterial;

	glm::vec3					m_Position[MAX_LINES];
	Color3f						m_Color[MAX_LINES];

	size_t						m_LineCount;

	VertexArray*				m_VAO;
	VertexBuffer*				m_PositionVBO;
	VertexBuffer*				m_ColorVBO;

public:

	GLLineRenderer();

	~GLLineRenderer();

	void AddLine(const glm::vec3& p0, const glm::vec3& p1, const Color3f& color_rgba = Color3f(1.0f));

	void Flush(const float* projection);

}; // class GLLineRenderer

#endif // __GL_LINE_RENDERER_H__
