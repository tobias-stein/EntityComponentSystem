///-------------------------------------------------------------------------------------------------
/// File:	BountySpawn.cpp.
///
/// Summary:	Implements the bounty spawn class.
///-------------------------------------------------------------------------------------------------

#include "BountySpawn.h"

BountySpawn::BountySpawn(const Position & position, const glm::vec2& halfExpand, const float orientation)
{
	AddComponent<SpawnComponent>(new RegionSpawn(position, glm::vec3(halfExpand, 0.0f), glm::vec3(0.0f, 0.0f, orientation)));

#ifdef DEBUG_SHOW_SPAWNS
	AddComponent<ShapeComponent>(ShapeGenerator::CreateShape<QuadShape>());
	AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(), Color4f(1.0f, 1.0f, 0.0f, 0.2f));

	TransformComponent* thisTransformComponent = GetComponent<TransformComponent>();
	thisTransformComponent->SetScale(glm::vec3(halfExpand, 0.0f));
#endif // DEBUG_SHOW_SPAWNS
}

BountySpawn::~BountySpawn()
{
}

SpawnInfo BountySpawn::GetSpawnInfo()
{
	return GetComponent<SpawnComponent>()->SampleRandomSpawnInfo(RandomSpawnSampler::Spherical);
}
