///-------------------------------------------------------------------------------------------------
/// File:	Collector.cpp.
///
/// Summary:	Implements the collector class.
///-------------------------------------------------------------------------------------------------

#include "Collector.h"

Collector::Collector(GameObjectId spawnId)
{
	AddComponent<ShapeComponent>(ShapeGenerator::CreateShape<TriangleShape>());
	AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	AddComponent<RespawnComponent>(DEFAULT_COLLECTOR_RESPAWNTIME, spawnId, true);
}

Collector::~Collector()
{}