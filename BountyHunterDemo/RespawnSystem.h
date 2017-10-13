///-------------------------------------------------------------------------------------------------
/// File:	RespawnSystem.h.
///
/// Summary:	Declares the respawn system class.
///-------------------------------------------------------------------------------------------------

#ifndef __RESPAWN_SYSTEM_H__
#define __RESPAWN_SYSTEM_H__

#include <ECS/ECS.h>


#include "WorldSystem.h"
#include "RespawnComponent.h"

class RespawnSystem : public ECS::System<RespawnSystem>, protected ECS::Event::IEventListener
{
	struct PendingRespawn
	{
		const ECS::EntityId	m_EntityID;

		float				m_RemainingDeathTime;

		const Position		m_RespawnPosition;

		// yaw, pitch, roll
		const glm::vec3		m_RespawnOrientation;

		PendingRespawn() :
			m_EntityID(ECS::INVALID_ENTITY_ID),
			m_RemainingDeathTime(-1.0f),
			m_RespawnPosition(INVALID_POSITION),
			m_RespawnOrientation(glm::vec3(0.0f))
		{}

		PendingRespawn(const ECS::EntityId id, float respawnTime, Position position = INVALID_POSITION, glm::vec3 orientation = glm::vec3(0.0f)) :
			m_EntityID(id),
			m_RemainingDeathTime(respawnTime),
			m_RespawnPosition(position),
			m_RespawnOrientation(orientation)
		{}

	}; // struct PendingRespawn

	using RespawnQueue = std::list<PendingRespawn>;

private:

	RespawnQueue m_RespawnQueue;

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	void OnGameObjectCreated(const GameObjectCreated* event);
	void OnGameObjectKilled(const GameObjectKilled* event);

public:

	RespawnSystem();
	virtual ~RespawnSystem();

	virtual void Update(float dt);

}; // class RespawnSystem

#endif // __RESPAWN_SYSTEM_H__
