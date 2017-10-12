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
#include "TransformComponent.h"

template<class T>
class GameObject : public ECS::Entity<T>
{
public:

	template<class... ARGS>
	GameObject(ARGS&... args)
	{
		
		AddComponent<TransformComponent>(std::forward<ARGS>(args)...);
		ECS::ECS_Engine->SendEvent<GameObjectCreated>(this->GetEntityID());
	}

	virtual ~GameObject()
	{
		ECS::ECS_Engine->SendEvent<GameObjectDestroyed>(this->GetEntityID());
	}

}; // class GameObject

#endif // __GAME_OBJECT_H__
