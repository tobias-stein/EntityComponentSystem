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

	T*		m_Pawn;

private:

	void OnKeyDownInternal(const KeyDownEvent* event)
	{
		this->OnKeyDown(event);
	}

	void OnKeyUpInternal(const KeyUpEvent* event)
	{
		this->OnKeyUp(event);
	}

	void OnKeyPressedInternal(const KeyPressedEvent* event)
	{
		this->OnKeyPressed(event);
	}

	void OnGamePaused(const GamePausedEvent* event)
	{
		UnregisterEventCallback(&PlayerController<T>::OnKeyDownInternal);
		UnregisterEventCallback(&PlayerController<T>::OnKeyUpInternal);
		UnregisterEventCallback(&PlayerController<T>::OnKeyPressedInternal);
	}

	void OnGameResumed(const GameResumedEvent* event)
	{
		RegisterEventCallback(&PlayerController<T>::OnKeyDownInternal);
		RegisterEventCallback(&PlayerController<T>::OnKeyUpInternal);
		RegisterEventCallback(&PlayerController<T>::OnKeyPressedInternal);
	}

public:

	PlayerController(const GameObjectId gameObjectId = INVALID_GAMEOBJECT_ID) :
		m_Pawn(nullptr)
	{
		if (gameObjectId != INVALID_GAMEOBJECT_ID)
			this->Possess(gameObjectId);

		RegisterEventCallback(&PlayerController<T>::OnGamePaused);
		RegisterEventCallback(&PlayerController<T>::OnGameResumed);
	}

	virtual ~PlayerController()
	{
		UnregisterEventCallback(&PlayerController<T>::OnGamePaused);
		UnregisterEventCallback(&PlayerController<T>::OnGameResumed);

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

		RegisterEventCallback(&PlayerController<T>::OnKeyDownInternal);
		RegisterEventCallback(&PlayerController<T>::OnKeyUpInternal);
		RegisterEventCallback(&PlayerController<T>::OnKeyPressedInternal);

		return true;
	}

	virtual void Unpossess() override
	{
		this->m_Pawn = nullptr;

		UnregisterEventCallback(&PlayerController<T>::OnKeyDownInternal);
		UnregisterEventCallback(&PlayerController<T>::OnKeyUpInternal);
		UnregisterEventCallback(&PlayerController<T>::OnKeyPressedInternal);
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