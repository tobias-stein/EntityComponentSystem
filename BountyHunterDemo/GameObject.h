///-------------------------------------------------------------------------------------------------
/// File:	GameObject.h.
///
/// Summary:	Declares the base game object entity class. Any object placed "physically", that is,
/// with 2D/3D coordinates in the virtual world must derive from this class.
///-------------------------------------------------------------------------------------------------


#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <ECS/ECS.h>

#include "GameEvents.h"
#include "GameConfiguration.h"

#include "TransformComponent.h"


template<class T>
class GameObject : public ECS::Entity<T>
{
public:

	GameObject()
	{
		AddComponent<TransformComponent>(Transform());
		ECS::ECS_Engine->SendEvent<GameObjectCreated>(this->GetEntityID());
	}

	GameObject(const Transform& transform)
	{		
		AddComponent<TransformComponent>(transform);
		ECS::ECS_Engine->SendEvent<GameObjectCreated>(this->GetEntityID());
	}

	virtual ~GameObject()
	{
		ECS::ECS_Engine->SendEvent<GameObjectDestroyed>(this->GetEntityID());
	}

}; // class GameObject

#endif // __GAME_OBJECT_H__
