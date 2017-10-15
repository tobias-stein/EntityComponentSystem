///-------------------------------------------------------------------------------------------------
/// File:	Bounty.cpp.
///
/// Summary:	Implements the bounty class.
///-------------------------------------------------------------------------------------------------

#include "Bounty.h"

Bounty::Bounty(GameObjectId spawnId)
{
	AddComponent<ShapeComponent>(ShapeGenerator::CreateShape<QuadShape>());
	AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	AddComponent<RespawnComponent>(BOUNTY_RESPAWNTIME, spawnId, true);
}

Bounty::~Bounty()
{
}
