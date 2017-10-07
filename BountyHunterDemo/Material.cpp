///-------------------------------------------------------------------------------------------------
/// File:	Material.cpp.
///
/// Summary:	Implements the material class.
///-------------------------------------------------------------------------------------------------

#include "Material.h"

Material::Material(const IMaterial* material) :
	m_materialData(material)
{}

Material::~Material()
{
	this->m_materialData = nullptr;
}