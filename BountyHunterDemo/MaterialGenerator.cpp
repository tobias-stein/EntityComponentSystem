///-------------------------------------------------------------------------------------------------
/// File:	MaterialGenerator.cpp.
///
/// Summary:	Implements the material generator class.
///-------------------------------------------------------------------------------------------------

#include "MaterialGenerator.h"
#include "Material.h"


MaterialGenerator::MaterialGenerator() :
	m_MaterialRegistry(IMaterial::MAX_MATERIALS, nullptr)
{}

MaterialGenerator::~MaterialGenerator()
{
	for (int i = 0; i < this->m_MaterialRegistry.size(); ++i)
	{
		this->m_MaterialRegistry[i]->Release();
		delete this->m_MaterialRegistry[i];
		this->m_MaterialRegistry[i] = nullptr;
	}
}
