#ifndef __ENTITY_BELLOW_SEA_LEVEL_EVENT_H__
#define __ENTITY_BELLOW_SEA_LEVEL_EVENT_H__


#include "ECS.h"

class EntityBellowSeaLevelEvent : public ECS::Event::Event<EntityBellowSeaLevelEvent>
{
public:

	float			currentHeight;


	EntityBellowSeaLevelEvent(ECS::EntityId id, float level) :
		Event(ECS::INVALID_ENTITY_ID, id),
		currentHeight(level)
	{}
};

#endif // __ENTITY_BELLOW_SEA_LEVEL_EVENT_H__