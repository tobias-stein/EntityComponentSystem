///-------------------------------------------------------------------------------------------------
/// File:	AIController.h.
///
/// Summary:	Declares the ai controller class.
///-------------------------------------------------------------------------------------------------

#ifndef __AI_CONTROLLER_H__
#define __AI_CONTROLLER_H__

#include "IController.h"

template<class T>
class AIController : public IController, ECS::Event::IEventListener
{
protected:

	T*	m_Pawn;

public:

	AIController(const GameObjectId gameObjectId = INVALID_GAMEOBJECT_ID) :
		m_Pawn(nullptr)
	{
		if (gameObjectId != INVALID_GAMEOBJECT_ID)
			this->Possess(gameObjectId);
	}

	virtual ~AIController()
	{
		this->Unpossess();
	}

	virtual bool Possess(const GameObjectId gameObjectId) override
	{
		ECS::IEntity* entity = ECS::ECS_Engine->GetEntityManager()->GetEntity(gameObjectId);

		if (entity == nullptr || entity->GetStaticEntityTypeID() != T::STATIC_ENTITY_TYPE_ID)
			return false;

		this->m_Pawn = static_cast<T*>(entity);
		if (this->m_Pawn == nullptr)
			return false;

		return true;
	}

	virtual void Unpossess() override
	{
		this->m_Pawn = nullptr;
	}

	virtual GameObjectId GetPossessed() const override
	{
		if (this->m_Pawn != nullptr)
			return this->m_Pawn->GetEntityID();

		return INVALID_GAMEOBJECT_ID;
	}

	virtual void Update(float dt) = 0;

}; // class AIController





#endif // __AI_CONTROLLER_H__