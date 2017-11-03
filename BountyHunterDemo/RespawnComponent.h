///-------------------------------------------------------------------------------------------------
/// File:	RespawnComponent.h.
///
/// Summary:	Declares the respawn component class.
///-------------------------------------------------------------------------------------------------


#ifndef __RESPAWN_COMPONENT_H__
#define __RESPAWN_COMPONENT_H__

#include "GameObject.h"

///-------------------------------------------------------------------------------------------------
/// Class:	RespawnComponent
///
/// Summary:	A respawn component. This component can be attached to any entity that has respawn 
/// ability. The RespawnSystem will take care of respawning the entity after it died.
///
/// Author:	Tobias Stein
///
/// Date:	12/10/2017
///-------------------------------------------------------------------------------------------------

class RespawnComponent : public ECS::Component<RespawnComponent>
{
public:

	/// Summary:	True to automatically respawn on death.
	bool			m_AutoRespawn;

	// time in seconds
	float			m_RespawnTime;

	Position		m_RespawnPosition;

	// yaw, pitch, roll
	glm::vec3		m_RespawnOrientation;

	GameObjectId	m_SpawnId;

	RespawnComponent(float respawnTime, const GameObjectId spawnId, bool autoRespawn = false) :
		m_AutoRespawn(autoRespawn),
		m_RespawnTime(respawnTime),
		m_RespawnPosition(INVALID_POSITION),
		m_RespawnOrientation(0.0f),
		m_SpawnId(spawnId)
	{}

	RespawnComponent(float respawnTime, bool autoRespawn = false, const Position& respawnPosition = INVALID_POSITION, const glm::vec3& respawnOrientation = glm::vec3(0.0f)) :
		m_AutoRespawn(autoRespawn),
		m_RespawnTime(respawnTime),
		m_RespawnPosition(respawnPosition),
		m_RespawnOrientation(respawnOrientation),
		m_SpawnId(INVALID_GAMEOBJECT_ID)
	{}

}; // class RespawnComponent

#endif // __RESPAWN_COMPONENT_H__