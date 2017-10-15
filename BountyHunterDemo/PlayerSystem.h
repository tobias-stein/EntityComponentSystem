///-------------------------------------------------------------------------------------------------
/// File:	PlayerSystem.h.
///
/// Summary:	Declares the player system class.
///-------------------------------------------------------------------------------------------------

#ifndef __PLAYER_SYSTEM_H__
#define __PLAYER_SYSTEM_H__

#include <ECS/ECS.h>

#include "Player.h"
 
class PlayerSystem : public ECS::System<PlayerSystem>
{
	using PlayerList = std::vector<Player*>;

private:

	PlayerList m_Players;

public:

	PlayerSystem();
	~PlayerSystem();

	///-------------------------------------------------------------------------------------------------
	/// Fn:	PlayerId PlayerSystem::AddNewPlayer(const char* playerName);
	///
	/// Summary:	Adds a new player to the game. Raises a PlayerJoined event.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	15/10/2017
	///
	/// Parameters:
	/// playerName - 	Name of the player.
	///
	/// Returns:	A PlayerId.
	///-------------------------------------------------------------------------------------------------

	PlayerId AddNewPlayer(const char* playerName, const Controller& controller = nullptr);

	///-------------------------------------------------------------------------------------------------
	/// Fn:	void PlayerSystem::RemovePlayer(PlayerId playerId);
	///
	/// Summary:	Removes a player described by playerId. Raises a PlayerLeft event.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	15/10/2017
	///
	/// Parameters:
	/// playerId - 	Identifier for the player.
	///-------------------------------------------------------------------------------------------------

	void RemovePlayer(PlayerId playerId);

	///-------------------------------------------------------------------------------------------------
	/// Fn:	inline Player* PlayerSystem::GetPlayer(PlayerId playerId) const
	///
	/// Summary:	Gets a player by its id.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	15/10/2017
	///
	/// Parameters:
	/// playerId - 	Identifier for the player.
	///
	/// Returns:	Null if it fails, else the player.
	///-------------------------------------------------------------------------------------------------

	inline Player* GetPlayer(PlayerId playerId) const 
	{ 
		assert(playerId < MAX_PLAYER && "Invalid player id!");
		return this->m_Players[playerId]; 
	}

}; // class PlayerSystem

#endif // __PLAYER_SYSTEM_H__