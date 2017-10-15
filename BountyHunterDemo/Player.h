///-------------------------------------------------------------------------------------------------
/// File:	Player.h.
///
/// Summary:	Declares the Player interface.
///-------------------------------------------------------------------------------------------------

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Controller.h"



class Player
{
protected:

	const PlayerId	m_PlayerID;

	std::string		m_PlayerName;

	/// Summary:	The active controller for this player.
	Controller		m_PlayerController;

public:

	Player(const PlayerId playerId, const char* playerName, const Controller& controller = nullptr);

	virtual ~Player();

	inline void SetPlayerName(const char* playerName) { this->m_PlayerName = playerName; }
	inline const char* GetPlayerName() const { return this->m_PlayerName.c_str(); }

	inline void SetController(Controller& controller) { this->m_PlayerController = controller; }
	inline Controller& GetController() { return this->m_PlayerController; }

}; // class IPlayer

#endif // __PLAYER_H__
