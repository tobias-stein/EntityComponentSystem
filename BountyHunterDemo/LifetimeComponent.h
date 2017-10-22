///-------------------------------------------------------------------------------------------------
/// File:	LifetimeComponent.h.
///
/// Summary:	Declares the lifetime component class.
///-------------------------------------------------------------------------------------------------

#ifndef __LIFE_TIME_COMPONENT_H__
#define __LIFE_TIME_COMPONENT_H__

#include <ECS/ECS.h>
#include "math.h"

class LifetimeComponent : public ECS::Component<LifetimeComponent>
{
public:
	
	float minLifetime;
	float maxLifetime;
	float currentLifetime;

	LifetimeComponent(float lifetime);
	LifetimeComponent(float min_lifetime, float max_lifetime);
	virtual ~LifetimeComponent();

	inline void ResetLifetime() { this->currentLifetime = glm::lerp(this->minLifetime, this->maxLifetime, glm::linearRand(0.0f, 1.0f)); }

}; // class LifetimeComponent

#endif // __LIFE_TIME_COMPONENT_H__