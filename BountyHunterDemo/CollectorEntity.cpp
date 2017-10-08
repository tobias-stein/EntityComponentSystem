///-------------------------------------------------------------------------------------------------
/// File:	CollectorEntity.cpp.
///
/// Summary:	Implements the collector class.
///-------------------------------------------------------------------------------------------------

#include "CollectorEntity.h"

#include "ShapeComponent.h"
#include "MaterialComponent.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"

CollectorEntity::CollectorEntity(bool humanPlayer)
{
	AddComponent<ShapeComponent>(ShapeGenerator::CreateShape<QuadShape>());
	AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
}

CollectorEntity::~CollectorEntity()
{}