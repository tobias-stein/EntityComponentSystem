#include "PlayerSpawn.h"


PlayerSpawn::PlayerSpawn(const Position & position, const float orientation)
{
	AddComponent<SpawnComponent>(new PointSpawn(position, glm::vec3(0.0f, 0.0f, orientation)));

#ifdef DEBUG_SHOW_SPAWNS
	AddComponent<ShapeComponent>(ShapeGenerator::CreateShape<QuadShape>());
	AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>(), Color4f(0.0f, 1.0f, 0.0f, 0.33f));
#endif // DEBUG_SHOW_SPAWNS
}

PlayerSpawn::~PlayerSpawn()
{
}

SpawnInfo PlayerSpawn::GetSpawnInfo()
{
	return GetComponent<SpawnComponent>()->GetSpawn().GetFixSpawnInfo();
}
