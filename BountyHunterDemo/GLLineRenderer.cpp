///-------------------------------------------------------------------------------------------------
/// File:	GLLineRenderer.cpp.
///
/// Summary:	Implements the gl 2D line renderer class.
///-------------------------------------------------------------------------------------------------

#include "GLLineRenderer.h"

#include "MaterialGenerator.h"

GLLineRenderer::GLLineRenderer() :
	m_LineCount(0),
	m_LineMaterial(MaterialGenerator::CreateMaterial<LineMaterial>())
{
	this->m_PositionVBO		= new VertexBuffer(MAX_LINES * sizeof(glm::vec3), true);
	this->m_ColorVBO		= new VertexBuffer(MAX_LINES * sizeof(Color3f), true);

	this->m_VAO				= new VertexArray();

	this->m_VAO->Bind();
	{
		// position attribute
		this->m_PositionVBO->Bind();
		MaterialVertexAttributeLoc positionVertexAttribute = this->m_LineMaterial.GetPositionVertexAttributeLocation();
		glEnableVertexAttribArray(positionVertexAttribute);
		glVertexAttribPointer(positionVertexAttribute, VERTEX_POSITION_DATA_ELEMENT_LEN, VERTEX_POSITION_DATA_TYPE, GL_FALSE, 0, BUFFER_OFFSET(0));

		// color attribute
		this->m_ColorVBO->Bind();
		MaterialVertexAttributeLoc colorVertexAttribute = this->m_LineMaterial.GetColorVertexAttributeLocation();
		glEnableVertexAttribArray(colorVertexAttribute);
		glVertexAttribPointer(colorVertexAttribute, VERTEX_COLOR_DATA_ELEMENT_LEN, VERTEX_COLOR_DATA_TYPE, GL_FALSE, 0, BUFFER_OFFSET(0));	
	}
	this->m_VAO->Unbind();
	this->m_ColorVBO->Unbind();
}

GLLineRenderer::~GLLineRenderer()
{
	if (this->m_VAO != nullptr)
	{
		delete this->m_VAO;
		this->m_VAO = nullptr;
	}

	if (this->m_PositionVBO != nullptr)
	{
		delete this->m_PositionVBO;
		this->m_PositionVBO = nullptr;
	}

	if (this->m_ColorVBO != nullptr)
	{
		delete this->m_ColorVBO;
		this->m_ColorVBO = nullptr;
	}
}

void GLLineRenderer::AddLine(const glm::vec3& p0, const glm::vec3& p1, const Color3f& color_rgb)
{
	if (this->m_LineCount >= MAX_LINES)
		return;

	this->m_Position[this->m_LineCount    ] = p0;
	this->m_Position[this->m_LineCount + 1] = p1;

	this->m_Color[this->m_LineCount    ]	= color_rgb;
	this->m_Color[this->m_LineCount + 1]	= color_rgb;

	this->m_LineCount += 2;
}

void GLLineRenderer::Flush(const float* projection, bool draw)
{
	if(draw == false)
		this->m_LineCount = 0;

	if (this->m_LineCount == 0)
		return;

	this->m_LineMaterial.Use();
	{
		this->m_LineMaterial.SetViewProjectionTransform(nullptr, projection);

		this->m_VAO->Bind();
		{
			this->m_PositionVBO->Bind();
			this->m_PositionVBO->Reset();
			this->m_PositionVBO->BufferVertexData(&this->m_Position[0], this->m_LineCount * sizeof(glm::vec3));

			this->m_ColorVBO->Bind();
			this->m_ColorVBO->Reset();
			this->m_ColorVBO->BufferVertexData(&this->m_Color[0], this->m_LineCount * sizeof(Color3f));

			glDrawArrays(GL_LINES, 0, this->m_LineCount);
			glGetLastError();
		}
	}
	this->m_LineMaterial.Unuse();
	this->m_LineCount = 0;
}
