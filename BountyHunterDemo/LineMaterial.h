///-------------------------------------------------------------------------------------------------
/// File:	LineMaterial.h.
///
/// Summary:	Declares the line material class.
///-------------------------------------------------------------------------------------------------

#ifndef __LINE_MATERIAL_H__
#define __LINE_MATERIAL_H__

#include "IMaterial.h"
#include "GLShader.h"


class LineMaterial : public IMaterial
{
	static constexpr const char* VERTEXT_SHADER =
	{
		SHADER_VERISON_330

		SHADER_DEFINE_INPUT_POSITION_VERTEX_ATTRIBUTE
		SHADER_DEFINE_INPUT_COLOR_VERTEX_ATTRIBUTE

		SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_PROJECTION_TRANSFORM, "mat4")

		"out " SHADER_IN_VERTEX_ATTRIBUTE_COLOR_TYPE " varColor;\n"

		"void main()\n"
		"{\n"
		"	varColor	= " SHADER_IN_VERTEX_ATTRIBUTE_COLOR_NAME ";\n"
		"	gl_Position = " SHADER_UNIFORM_PROJECTION_TRANSFORM " * vec4(" SHADER_IN_VERTEX_ATTRIBUTE_POSITION_NAME ", 1.0);\n"
		"}\n"
	};

	static constexpr const char* FRAGMENT_SHADER =
	{
		SHADER_VERISON_330

		SHADER_DEFINE_OUTPUT_COLOR_VERTEX_ATTRIBUTE

		"in " SHADER_IN_VERTEX_ATTRIBUTE_COLOR_TYPE	" varColor;\n"

		"void main()\n"
		"{\n"
		"	" SHADER_OUT_VERTEX_ATTRIBUTE_COLOR_NAME " = vec4(varColor, 1.0);\n"
		"}\n"
	};

private:

	ShaderProgram* m_ShaderProgram;

public:

	static constexpr Type MATERIAL_TYPE { LINE_MATERIAL };

	LineMaterial();

	virtual ~LineMaterial();

	virtual inline const MaterialID GetMaterialID() const override { return MATERIAL_TYPE; }

	virtual void Use() const override;

	virtual void Unuse() const override;

	virtual bool Initialize() override;

	virtual void Release() override;

	virtual void SetModelTransform(const float* model) override
	{
	}

	virtual void SetViewProjectionTransform(const float* view, const float* proj) override
	{
		if (this->m_ShaderProgram != nullptr)
		{
			glUniformMatrix4fv((*this->m_ShaderProgram)(SHADER_UNIFORM_PROJECTION_TRANSFORM), 1, GL_FALSE, (const GLfloat*)proj);
		}
	}

	virtual const MaterialVertexAttributeLoc GetPositionVertexAttributeLocation() const override
	{
		return POSITION_MATERIAL_VERTEX_ATTRIBUTE_LOC;
	}

	virtual const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation() const override
	{
		return -1;
	}

	virtual const MaterialVertexAttributeLoc GetTexCoordVertexAttributeLocation() const override
	{
		return -1;
	}

	virtual const MaterialVertexAttributeLoc GetColorVertexAttributeLocation() const override
	{
		return COLOR_MATERIAL_VERTEX_ATTRIBUTE_LOC;
	}


	virtual void SetUniform4fv(const char* uniformName, const float* vec4) override
	{
		if (this->m_ShaderProgram != nullptr)
		{
			glUniform4fv((*this->m_ShaderProgram)(uniformName), 1, (const GLfloat*)vec4);
		}
	}

	virtual void SetUniformMatrix4fv(const char* uniformName, const float* mat4) override
	{
		if (this->m_ShaderProgram != nullptr)
		{
			glUniformMatrix4fv((*this->m_ShaderProgram)(uniformName), 1, GL_FALSE, (const GLfloat*)mat4);
		}
	}

}; // class LineMaterial

#endif // __LINE_MATERIAL_H__
