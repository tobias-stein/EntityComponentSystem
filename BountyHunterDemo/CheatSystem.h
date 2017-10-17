///-------------------------------------------------------------------------------------------------
/// File:	CheatSystem.h.
///
/// Summary:	Declares the cheat system class.
///-------------------------------------------------------------------------------------------------

#ifndef __CHEAT_SYSTEM_H__
#define __CHEAT_SYSTEM_H__

#include <ECS/ECS.h>

#include "GameObject.h"

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
	using ActivePlayers		= std::list<PlayerId>;

	using SelectedPlayers	= ActivePlayers::iterator;

private:

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();


	void OnGameObjectCreated(const GameObjectCreated* event);
	void OnGameObjectDestroyed(const GameObjectDestroyed* event);

	void OnPlayerJoined(const PlayerJoined* event);
	void OnPlayerLeft(const PlayerLeft* event);

	void OnKeyDownEvent(const KeyDownEvent* event);


	ActivePlayers	m_Players;
	SelectedPlayers	m_SelectedPlayer;

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