///-------------------------------------------------------------------------------------------------
/// File:	RespawnComponent.h.
///
/// Summary:	Declares the respawn component class.
///-------------------------------------------------------------------------------------------------


#ifndef __RESPAWN_COMPONENT_H__
#define __RESPAWN_COMPONENT_H__

#include "ECS/ECS.h"

#include "IWorld.h"

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

	// time in seconds
	float		m_RespawnTime;

	Position	m_RespawnPosition;

	// yaw, pitch, roll
	glm::vec3	m_RespawnOrientation;

	RespawnComponent(float respawnTime, const Position& respawnPosition = INAVLID_POSITION, const glm::vec3& respawnOrientation = glm::vec3(0.0f)) :
		m_RespawnTime(respawnTime),
		m_RespawnPosition(respawnPosition),
		m_RespawnOrientation(respawnOrientation)
	{}

}; // class RespawnComponent

#endif // __RESPAWN_COMPONENT_H__