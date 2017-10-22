///-------------------------------------------------------------------------------------------------
/// File:	LifetimeComponent.cpp.
///
/// Summary:	Implements the lifetime component class.
///-------------------------------------------------------------------------------------------------

#include "LifetimeComponent.h"

LifetimeComponent::LifetimeComponent(float lifetime) :
	minLifetime(lifetime),
	maxLifetime(lifetime),
	currentLifetime(lifetime)
{
}

LifetimeComponent::LifetimeComponent(float min_lifetime, float max_lifetime) :
	minLifetime(min_lifetime),
	maxLifetime(max_lifetime)
{
	ResetLifetime();
}

LifetimeComponent::~LifetimeComponent()
{
}
