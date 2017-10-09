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

		"out " SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_TYPE		" outNormal;\n"
		"out " SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_TYPE		" outTexCoord;\n"
		"out " SHADER_IN_VERTEX_ATTRIBUTE_COLOR_TYPE		" outColor;\n"

		"void main()\n"
		"{\n"		
		"	outNormal	= " SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_NAME ";\n"
		"	outTexCoord	= " SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_NAME ";\n"
		"	outColor	= " SHADER_IN_VERTEX_ATTRIBUTE_COLOR_NAME ";\n"

		"	gl_Position = (" SHADER_UNIFORM_PROJECTION_TRANSFORM " * " SHADER_UNIFORM_VIEW_TRANSFORM " * " SHADER_UNIFORM_MODEL_TRANSFORM ") * vec4(" SHADER_IN_VERTEX_ATTRIBUTE_POSITION_NAME ", 1.0);\n"
		"}\n"
	};

	static constexpr const char* FRAGMENT_SHADER = 
	{
		SHADER_VERISON_330

		SHADER_DEFINE_OUTPUT_COLOR_VERTEX_ATTRIBUTE

		"in " SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_TYPE	" inNormal;\n"
		"in " SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_TYPE	" inTexCoord;\n"
		"in " SHADER_IN_VERTEX_ATTRIBUTE_COLOR_TYPE		" inColor;\n"

		SHADER_DEFINE_SAMPLER2D("texSampler")

		"void main()\n"
		"{\n"
		"	vec4 texColor = texture(texSampler, inTexCoord);\n"
		//"	" SHADER_OUT_VERTEX_ATTRIBUTE_COLOR_NAME " = mix( texColor, vec4(inColor, 1.0), 0.5 );\n"
		"	" SHADER_OUT_VERTEX_ATTRIBUTE_COLOR_NAME " = vec4(0.0, 1.0, 1.0, 1.0);\n"
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

	virtual void SetViewProjectionTransform(const float* view, const float* proj) override
	{
		if (this->m_ShaderProgram != nullptr)
		{
			this->m_ShaderProgram->Use();
			{
				glUniformMatrix4fv((*this->m_ShaderProgram)(SHADER_UNIFORM_VIEW_TRANSFORM), 1, GL_FALSE, (const GLfloat*)view);
				glUniformMatrix4fv((*this->m_ShaderProgram)(SHADER_UNIFORM_PROJECTION_TRANSFORM), 1, GL_FALSE, (const GLfloat*)proj);
			}
			this->m_ShaderProgram->Unuse();
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

}; // class DefaultMaterial

#endif // __DEFAULT_MATERIAL_H__
