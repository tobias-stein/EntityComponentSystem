///-------------------------------------------------------------------------------------------------
/// File:	IMaterial.h.
///
/// Summary:	Declares the base Material interface.
///-------------------------------------------------------------------------------------------------


#ifndef __I_MATERIAL_H__
#define __I_MATERIAL_H__

#include <stdint.h>

typedef uint16_t MaterialID;

static constexpr MaterialID INVALID_MATERIAL_ID { 0xffff };

class IMaterial
{
public:

	IMaterial();
	virtual ~IMaterial();

	virtual inline const MaterialID GetMaterialID() const { return INVALID_MATERIAL_ID; }

	virtual void Use() = 0;

	virtual void Unuse() = 0;

	virtual bool Initialize() { return true; }

	virtual void Release() {}

};

#endif // __I_MATERIAL_H__
