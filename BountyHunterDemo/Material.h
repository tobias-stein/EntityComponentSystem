///-------------------------------------------------------------------------------------------------
/// File:	Material.h.
///
/// Summary:	Declares a Material handle.
///-------------------------------------------------------------------------------------------------


#ifndef __MATERIAL_H__
#define __MATERIAL_H__

// incldue materials
#include "DefaultMaterial.h"


class Material
{
private:

	IMaterial* m_materialData;

public:

	Material(IMaterial* material);
	~Material();


	// Forward functions

	inline const MaterialID GetMaterialID() const { return this->m_materialData->GetMaterialID(); }

	void Use() const { const_cast<IMaterial*>(this->m_materialData)->Use(); }

	void Unuse() const { const_cast<IMaterial*>(this->m_materialData)->Unuse(); }

	void SetModelTransform(const float* model) { this->m_materialData->SetModelTransform(model); }

	void SetViewProjectionTransform(const float* view, const float* proj) { this->m_materialData->SetViewProjectionTransform(view, proj); };

	const MaterialVertexAttributeLoc GetPositionVertexAttributeLocation() const { return this->m_materialData->GetPositionVertexAttributeLocation(); }

	const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation() const { return this->m_materialData->GetNormalVertexAttributeLocation(); }

	const MaterialVertexAttributeLoc GetTexCoordVertexAttributeLocation() const { return this->m_materialData->GetTexCoordVertexAttributeLocation(); }

	const MaterialVertexAttributeLoc GetColorVertexAttributeLocation() const { return this->m_materialData->GetColorVertexAttributeLocation(); }
};

#endif // __MATERIAL_H__
