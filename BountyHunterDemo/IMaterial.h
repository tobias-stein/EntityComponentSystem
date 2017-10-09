///-------------------------------------------------------------------------------------------------
/// File:	IMaterial.h.
///
/// Summary:	Declares the base Material interface.
///-------------------------------------------------------------------------------------------------


#ifndef __I_MATERIAL_H__
#define __I_MATERIAL_H__


#define SHADER_VERISON_330											"#version 330\n"

#define SHADER_DEFINE_INPUT_VERTEX_ATTRIBUTE(name, type, location)	"layout(location=" #location ") in " type " " name ";\n"
#define SHADER_DEFINE_OUTPUT_VERTEX_ATTRIBUTE(name, type, location)	"layout(location=" #location ") out " type " " name ";\n"

#define SHADER_DEFINE_UNIFORM(name, type)							"uniform " type " " name ";\n"

#define SHADER_DEFINE_SAMPLER2D(name)								SHADER_DEFINE_UNIFORM(name, "sampler2D")


// DEFAULT INPUT VERTEX ATTRIBUTES	
#define	SHADER_IN_VERTEX_ATTRIBUTE_POSITION_NAME					"vPosition"
#define	SHADER_IN_VERTEX_ATTRIBUTE_POSITION_TYPE					"vec3"

#define	SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_NAME						"vNormal"
#define	SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_TYPE						"vec3"

#define	SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_NAME					"vTexCoord"
#define	SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_TYPE					"vec2"

#define SHADER_IN_VERTEX_ATTRIBUTE_COLOR_NAME						"vColor"
#define	SHADER_IN_VERTEX_ATTRIBUTE_COLOR_TYPE						"vec3"


#define SHADER_DEFINE_INPUT_POSITION_VERTEX_ATTRIBUTE				SHADER_DEFINE_INPUT_VERTEX_ATTRIBUTE(SHADER_IN_VERTEX_ATTRIBUTE_POSITION_NAME,	SHADER_IN_VERTEX_ATTRIBUTE_POSITION_TYPE,	0)
#define SHADER_DEFINE_INPUT_NORMAL_VERTEX_ATTRIBUTE					SHADER_DEFINE_INPUT_VERTEX_ATTRIBUTE(SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_NAME,	SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_TYPE,		1)
#define SHADER_DEFINE_INPUT_TEXCOORD_VERTEX_ATTRIBUTE				SHADER_DEFINE_INPUT_VERTEX_ATTRIBUTE(SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_NAME,	SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_TYPE,	2)
#define SHADER_DEFINE_INPUT_COLOR_VERTEX_ATTRIBUTE					SHADER_DEFINE_INPUT_VERTEX_ATTRIBUTE(SHADER_IN_VERTEX_ATTRIBUTE_COLOR_NAME,		SHADER_IN_VERTEX_ATTRIBUTE_COLOR_TYPE,		3)



// DEFAULT OUTPUT VERTEX ATTRIBUTES	
#define SHADER_OUT_VERTEX_ATTRIBUTE_COLOR_NAME						"vColor"
#define	SHADER_OUT_VERTEX_ATTRIBUTE_COLOR_TYPE						"vec4"


#define SHADER_DEFINE_OUTPUT_COLOR_VERTEX_ATTRIBUTE					SHADER_DEFINE_OUTPUT_VERTEX_ATTRIBUTE(SHADER_OUT_VERTEX_ATTRIBUTE_COLOR_NAME,	SHADER_OUT_VERTEX_ATTRIBUTE_COLOR_TYPE,		0)


// DEFAULT SHADER UNIFORMS
#define SHADER_UNIFORM_MODEL_TRANSFORM								"uModelTransform"
#define SHADER_UNIFORM_VIEW_TRANSFORM								"uViewTransform"
#define SHADER_UNIFORM_PROJECTION_TRANSFORM							"uProjectionTransform"




#include <stdint.h>

typedef uint16_t MaterialID;
typedef uint32_t MaterialVertexAttributeLoc;

static constexpr MaterialID					INVALID_MATERIAL_ID						{ 0xffff };
static constexpr MaterialVertexAttributeLoc	INVALID_MATERIAL_VERTEX_ATTRIBUTE_LOC	{ 0xffffffff };

static constexpr MaterialVertexAttributeLoc POSITION_MATERIAL_VERTEX_ATTRIBUTE_LOC	{ 0 };
static constexpr MaterialVertexAttributeLoc NORMAL_MATERIAL_VERTEX_ATTRIBUTE_LOC	{ 1 };
static constexpr MaterialVertexAttributeLoc TEXCOORD_MATERIAL_VERTEX_ATTRIBUTE_LOC	{ 2 };
static constexpr MaterialVertexAttributeLoc COLOR_MATERIAL_VERTEX_ATTRIBUTE_LOC		{ 3 };

class IMaterial
{
public:

	enum Type
	{
		INVALID_MATERIAL = INVALID_MATERIAL_ID,

		DEFAULT_MATERIAL = 0,


		MAX_MATERIALS
	}; // enum Type


	IMaterial();
	virtual ~IMaterial();

	virtual inline const MaterialID GetMaterialID() const { return INVALID_MATERIAL_ID; }

	virtual void Use() const = 0;

	virtual void Unuse() const = 0;

	virtual bool Initialize() = 0;

	virtual void Release() = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual void IMaterial::SetModelTransform(const float* model) = 0;
	///
	/// Summary:	Sets model transform uniform, if shader supports it.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	9/10/2017
	///
	/// Parameters:
	/// model - 	The model.
	///-------------------------------------------------------------------------------------------------

	virtual void SetModelTransform(const float* model) = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:
	/// virtual void IMaterial::SetViewPerspectiveTransform(const float* view, const float* pers) = 0;
	///
	/// Summary:	If the material uses shader with view and/or perspective transformation they can by applied here.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	8/10/2017
	///
	/// Parameters:
	/// view - 	   	The view.
	/// pers - 	   	The proj.
	///-------------------------------------------------------------------------------------------------

	virtual void SetViewProjectionTransform(const float* view, const float* proj) = 0;

	virtual const MaterialVertexAttributeLoc GetPositionVertexAttributeLocation() const = 0;

	virtual const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation() const = 0;

	virtual const MaterialVertexAttributeLoc GetTexCoordVertexAttributeLocation() const = 0;

	virtual const MaterialVertexAttributeLoc GetColorVertexAttributeLocation() const = 0;
};

#endif // __I_MATERIAL_H__
