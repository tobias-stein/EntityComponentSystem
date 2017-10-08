///-------------------------------------------------------------------------------------------------
/// File:	MaterialGenerator.h.
///
/// Summary:	Declares the material generator class.
///-------------------------------------------------------------------------------------------------


#ifndef __MATERIAL_GENERATOR_H__
#define __MATERIAL_GENERATOR_H__

#include "Material.h"

#include <vector>

class Material;

class MaterialGenerator
{
	using MaterialRegistry = std::vector<IMaterial*>;

private:

	MaterialGenerator();

	MaterialGenerator(const MaterialGenerator&) = delete;
	MaterialGenerator& operator=(const MaterialGenerator&) = delete;

	MaterialRegistry m_MaterialRegistry;

	static MaterialGenerator& GetInstance()
	{
		static MaterialGenerator INSTANCE;
		return INSTANCE;
	}

public:	

	~MaterialGenerator();

	template<class M>
	static Material CreateMaterial()
	{
		MaterialGenerator& instance = MaterialGenerator::GetInstance();

		IMaterial* material = nullptr;

		material = instance.m_MaterialRegistry[M::MATERIAL_TYPE];

		// return a new material of this type
		if (material != nullptr)
			return Material(material);


		// material type not instantiated yet
		material = new M;
		
		assert(material->Initialize() && "Failed to initialize material!");
		SDL_Log("Material #%d initialized.", M::MATERIAL_TYPE);

		instance.m_MaterialRegistry[M::MATERIAL_TYPE] = material;

		return Material(material);
	}

}; // class ShapeGenerator

#endif // __MATERIAL_GENERATOR_H__
