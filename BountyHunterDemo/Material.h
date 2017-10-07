///-------------------------------------------------------------------------------------------------
/// File:	Material.h.
///
/// Summary:	Declares a Material handle.
///-------------------------------------------------------------------------------------------------


#ifndef __MATERIAL_H__
#define __MATERIAL_H__

// incldue materials
#include "IMaterial.h"


class Material
{
private:

	const IMaterial* m_materialData;

public:

	Material(const IMaterial* material);
	~Material();


	// Forward functions

	inline const MaterialID GetMaterialID() const { return this->m_materialData->GetMaterialID(); }

	void Use() { const_cast<IMaterial*>(this->m_materialData)->Use(); }

	void Unuse() { const_cast<IMaterial*>(this->m_materialData)->Unuse(); }
};

#endif // __MATERIAL_H__
