///-------------------------------------------------------------------------------------------------
/// File:	CheatSystem.h.
///
/// Summary:	Declares the cheat system class.
///-------------------------------------------------------------------------------------------------

#ifndef __CHEAT_SYSTEM_H__
#define __CHEAT_SYSTEM_H__

#include <ECS/ECS.h>

#include "GameObject.h"

#include "ControllerComponent.h"

///-------------------------------------------------------------------------------------------------
/// Class:	CheatSystem
///
/// Summary:	A cheat system that's mainly intend for test purpose.
///
/// Author:	Tobias Stein
///
/// Date:	15/10/2017
///-------------------------------------------------------------------------------------------------

class CheatSystem : public ECS::System<CheatSystem>, public ECS::Event::IEventListener
{
	using RegisteredController = std::list<ControllerComponent*>;

	using ActivePlayerController = RegisteredController::iterator;

private:

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();


	void OnGameObjectCreated(const GameObjectCreated* event);
	void OnGameObjectDestroyed(const GameObjectDestroyed* event);

	void OnKeyDownEvent(const KeyDownEvent* event);


	RegisteredController	m_Controller;
	ActivePlayerController	m_ActivePlayerController;

public:

	CheatSystem();

	virtual ~CheatSystem();

// Cheats
private:

	void KillAllCollectorGameObjects();
	void KillAllBountyGameObjects();

	void PossessCollector();
	void UnpossessCollector();
	void PossessNextCollector();
	void PossessPrevCollector();

	void DoPossessCollector();
	void DoUnpossessCollector();

}; // class CheatSystem

#endif // __CHEAT_SYSTEM_H__