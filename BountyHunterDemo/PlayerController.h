///-------------------------------------------------------------------------------------------------
/// File:	PlayerController.h.
///
/// Summary:	Declares the player controller class.
///-------------------------------------------------------------------------------------------------

#ifndef __PLAYER_CONTROLLER_H__
#define __PLAYER_CONTROLLER_H__

#include "IController.h"

template<class T>
class PlayerController : public IController, ECS::Event::IEventListener
{
protected:

	T*	m_Pawn;

public:

	PlayerController() :
		m_Pawn(nullptr)
	{
		RegisterEventCallback(&PlayerController<T>::OnKeyDown);
		RegisterEventCallback(&PlayerController<T>::OnKeyUp);
		RegisterEventCallback(&PlayerController<T>::OnKeyPressed);
	}

	virtual ~PlayerController()
	{
		this->m_Pawn = nullptr;

		UnregisterEventCallback(&PlayerController<T>::OnKeyDown);
		UnregisterEventCallback(&PlayerController<T>::OnKeyUp);
		UnregisterEventCallback(&PlayerController<T>::OnKeyPressed);
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

	virtual void OnKeyDown(const KeyDownEvent* event) = 0;
	virtual void OnKeyUp(const KeyUpEvent* event) = 0;
	virtual void OnKeyPressed(const KeyPressedEvent* event) = 0;

}; // class PlayerController





#endif // __PLAYER_CONTROLLER_H__