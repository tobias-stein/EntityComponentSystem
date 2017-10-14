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

	inline void Use() const { const_cast<IMaterial*>(this->m_materialData)->Use(); }

	inline void Unuse() const { const_cast<IMaterial*>(this->m_materialData)->Unuse(); }

	inline void SetModelTransform(const float* model) { this->m_materialData->SetModelTransform(model); }

	inline void SetViewProjectionTransform(const float* view, const float* proj) { this->m_materialData->SetViewProjectionTransform(view, proj); };

	inline const MaterialVertexAttributeLoc GetPositionVertexAttributeLocation() const { return this->m_materialData->GetPositionVertexAttributeLocation(); }

	inline const MaterialVertexAttributeLoc GetNormalVertexAttributeLocation() const { return this->m_materialData->GetNormalVertexAttributeLocation(); }

	inline const MaterialVertexAttributeLoc GetTexCoordVertexAttributeLocation() const { return this->m_materialData->GetTexCoordVertexAttributeLocation(); }

	inline const MaterialVertexAttributeLoc GetColorVertexAttributeLocation() const { return this->m_materialData->GetColorVertexAttributeLocation(); }

	inline void SetUniform4fv(const char* uniformName, const float* vec4) { this->m_materialData->SetUniform4fv(uniformName, vec4); }
	inline void SetUniformMatrix4fv(const char* uniformName, const float* mat4) { this->m_materialData->SetUniformMatrix4fv(uniformName, mat4); }
};

#endif // __MATERIAL_H__
