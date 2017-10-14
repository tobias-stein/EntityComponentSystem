///-------------------------------------------------------------------------------------------------
/// File:	SpawnComponent.cpp.
///
/// Summary:	Implements the spawn componenth class.
///-------------------------------------------------------------------------------------------------

#include "SpawnComponent.h"

SpawnComponent::SpawnComponent(const Spawn& spawn) :
	Spawn(spawn)
{}

SpawnComponent::~SpawnComponent()
{
	DeleteSpawn();
}
