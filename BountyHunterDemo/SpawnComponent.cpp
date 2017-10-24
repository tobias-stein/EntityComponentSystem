///-------------------------------------------------------------------------------------------------
/// File:	SpawnComponent.cpp.
///
/// Summary:	Implements the spawn componenth class.
///-------------------------------------------------------------------------------------------------

#include "SpawnComponent.h"

SpawnComponent::SpawnComponent(const Spawn& spawn) :
	m_Spawn(spawn)
{}

SpawnComponent::~SpawnComponent()
{
	this->m_Spawn.DeleteSpawn();
}
