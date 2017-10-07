///-------------------------------------------------------------------------------------------------
/// File:	IMaterial.h.
///
/// Summary:	Declares the base Material interface.
///-------------------------------------------------------------------------------------------------


#ifndef __I_MATERIAL_H__
#define __I_MATERIAL_H__

#include <stdint.h>

typedef uint16_t MaterialID;
typedef uint32_t MaterialVertexAttributeID;

static constexpr MaterialID					INVALID_MATERIAL_ID { 0xffff };
static constexpr MaterialVertexAttributeID	INVALID_MATERIAL_VERTEX_ATTRIBUTE_ID { 0xffffffff };

class IMaterial
{
public:

	IMaterial();
	virtual ~IMaterial();

	virtual inline const MaterialID GetMaterialID() const { return INVALID_MATERIAL_ID; }

	virtual void Use() const = 0;

	virtual void Unuse() const = 0;

	virtual bool Initialize() { return true; }

	virtual void Release() {}


	virtual const MaterialVertexAttributeID GetPositionVertexAttributeLocation() const = 0;

	virtual const MaterialVertexAttributeID GetNormalVertexAttributeLocation() const = 0;

	virtual const MaterialVertexAttributeID GetTexCoordVertexAttributeLocation() const = 0;

	virtual const MaterialVertexAttributeID GetColorVertexAttributeLocation() const = 0;
};

#endif // __I_MATERIAL_H__
