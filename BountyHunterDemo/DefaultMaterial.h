///-------------------------------------------------------------------------------------------------
/// File:	DefaultMaterial.h.
///
/// Summary:	Declares the default material class.
///-------------------------------------------------------------------------------------------------

#ifndef __DEFAULT_MATERIAL_H__
#define __DEFAULT_MATERIAL_H__

#include "IMaterial.h"
#include "GLShader.h"


class DefaultMaterial : public IMaterial
{
	static constexpr const char* VERTEXT_SHADER =
	{
		SHADER_VERISON_330

		SHADER_DEFINE_INPUT_POSITION_VERTEX_ATTRIBUTE
		SHADER_DEFINE_INPUT_NORMAL_VERTEX_ATTRIBUTE
		SHADER_DEFINE_INPUT_TEXCOORD_VERTEX_ATTRIBUTE
		SHADER_DEFINE_INPUT_COLOR_VERTEX_ATTRIBUTE

		SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_MODEL_TRANSFORM,		"mat4")
		SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_VIEW_TRANSFORM,		"mat4")
		SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_PROJECTION_TRANSFORM,	"mat4")
		SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_COLOR0,				SHADER_UNIFORM_COLOR0_TYPE)

		"out " SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_TYPE		" varNormal;\n"
		"out " SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_TYPE		" varTexCoord;\n"
		"out " SHADER_UNIFORM_COLOR0_TYPE					" varColor;\n"

		"void main()\n"
		"{\n"
		"	varNormal	= " SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_NAME ";\n"
		"	varTexCoord	= " SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_NAME ";\n"
		"	varColor	= " SHADER_UNIFORM_COLOR0 ";\n"

		"	gl_Position = (" SHADER_UNIFORM_PROJECTION_TRANSFORM " * " SHADER_UNIFORM_VIEW_TRANSFORM " * " SHADER_UNIFORM_MODEL_TRANSFORM ") * vec4(" SHADER_IN_VERTEX_ATTRIBUTE_POSITION_NAME ", 1.0);\n"
		"}\n"
	};

	static constexpr const char* FRAGMENT_SHADER =
	{
		SHADER_VERISON_330

		SHADER_DEFINE_OUTPUT_COLOR_VERTEX_ATTRIBUTE

		"in " SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_TYPE	" varNormal;\n"
		"in " SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_TYPE	" varTexCoord;\n"
		"in " SHADER_UNIFORM_COLOR0_TYPE				" varColor;\n"

		//SHADER_DEFINE_SAMPLER2D("texSampler")

		"void main()\n"
		"{\n"
		//"	vec4 texColor = texture(texSampler, varTexCoord);\n"
		//"	" SHADER_OUT_VERTEX_ATTRIBUTE_COLOR_NAME " = mix( texColor, vec4(varColor, 1.0), 0.5 );\n"
		"	" SHADER_OUT_VERTEX_ATTRIBUTE_COLOR_NAME " = varColor;\n"
		"}\n"
	};

private:

	ShaderProgram* m_ShaderProgram;

public:

	static constexpr Type MATERIAL_TYPE { DEFAULT_MATERIAL };

	DefaultMaterial();

	virtual ~DefaultMaterial();

	virtual inline const MaterialID GetMaterialID() const override { return MATERIAL_TYPE; }

	virtual void Use() const override;

	virtual void Unuse() const override;

	virtual bool Initialize() override;

	virtual void Release() override;

	virtual void SetModelTransform(const float* model)
	{
		if (this->m_ShaderProgram != nullptr)
		{
			glUniformMatrix4fv((*this->m_ShaderProgram)(SHADER_UNIFORM_MODEL_TRANSFORM), 1, GL_FALSE, (const GLfloat*)model);
		}
	}

	virtual void SetViewProjectionTransform(const float* view, const float* proj) override
	{
		if (this->m_ShaderProgram != nullptr)
		{
			glUniformMatrix4fv((*this->m_ShaderProgram)(SHADER_UNIFORM_VIEW_TRANSFORM), 1, GL_FALSE, (const GLfloat*)view);
			glUniformMatrix4fv((*this->m_ShaderProgram)(SHADER_UNIFORM_PROJECTION_TRANSFORM), 1, GL_FALSE, (const GLfloat*)proj);
		}
	}

	virtual const MaterialVertexAttributeLoc GetPositionVertexAttributeLocation() const override
	{
		return POSITION_MATERIAL_VERTEX_ATTRIBUTE_LOC;
	}

	virtual const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation() const override
	{
		return NORMAL_MATERIAL_VERTEX_ATTRIBUTE_LOC;
	}

	virtual const MaterialVertexAttributeLoc GetTexCoordVertexAttributeLocation() const override
	{
		return TEXCOORD_MATERIAL_VERTEX_ATTRIBUTE_LOC;
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

}; // class DefaultMaterial

#endif // __DEFAULT_MATERIAL_H__
