///-------------------------------------------------------------------------------------------------
/// File:	Collector.cpp.
///
/// Summary:	Implements the collector class.
///-------------------------------------------------------------------------------------------------

#include "Collector.h"

#include "ShapeComponent.h"
#include "MaterialComponent.h"
#include "RespawnComponent.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"

Collector::Collector(GameObjectId spawnId, IController* controller)
{
	AddComponent<ShapeComponent>(ShapeGenerator::CreateShape<TriangleShape>());
	AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	AddComponent<RespawnComponent>(COLLECTOR_RESPAWNTIME, spawnId, true);
	AddComponent<ControllerComponent>(controller);
}

Collector::~Collector()
{}