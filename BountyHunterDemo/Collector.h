///-------------------------------------------------------------------------------------------------
/// File:	Collector.h.
///
/// Summary:	Declares the collector entity class.
///-------------------------------------------------------------------------------------------------


#ifndef __COLLECTOR_ENTITY_H__
#define __COLLECTOR_ENTITY_H__

#include "GameObject.h"

#include "ShapeComponent.h"
#include "MaterialComponent.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"

class Collector : public GameObject<Collector>
{
public:

	template<class... ARGS>
	Collector(ARGS&... args) : GameObject(std::forward<ARGS>(args)...)
	{
		AddComponent<ShapeComponent>(ShapeGenerator::CreateShape<TriangleShape>());
		AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	}

	virtual ~Collector()
	{}

}; // class Collector

#endif // __COLLECTOR_ENTITY_H__
