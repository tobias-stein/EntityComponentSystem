///-------------------------------------------------------------------------------------------------
/// File:	RespawnSystem.h.
///
/// Summary:	Declares the respawn system class.
///-------------------------------------------------------------------------------------------------

#ifndef __RESPAWN_SYSTEM_H__
#define __RESPAWN_SYSTEM_H__

#include <ECS/ECS.h>

#include "GameObjectSpawn.h"
#include "RespawnComponent.h"

class RespawnSystem : public ECS::System<RespawnSystem>, protected ECS::Event::IEventListener
{
	struct PendingRespawn
	{
		const GameObjectId	m_spawnableID;

		const GameObjectId	m_spawnID;

		float				m_RemainingDeathTime;

		const Position		m_RespawnPosition;

		// yaw, pitch, roll
		const glm::vec3		m_RespawnOrientation;

		PendingRespawn() :
			m_spawnableID(ECS::INVALID_ENTITY_ID),
			m_spawnID(ECS::INVALID_ENTITY_ID),
			m_RemainingDeathTime(-1.0f),
			m_RespawnPosition(INVALID_POSITION),
			m_RespawnOrientation(glm::vec3(0.0f))
		{}

		PendingRespawn(GameObjectId id, float respawnTime, Position position = INVALID_POSITION, glm::vec3 orientation = glm::vec3(0.0f)) :
			m_spawnableID(id),
			m_RemainingDeathTime(respawnTime),
			m_RespawnPosition(position),
			m_RespawnOrientation(orientation)
		{}

		PendingRespawn(GameObjectId id, GameObjectId spawnId, float respawnTime) :
			m_spawnableID(id),
			m_spawnID(spawnId),
			m_RemainingDeathTime(respawnTime)
		{}

	}; // struct PendingRespawn

	using RespawnQueue = std::list<PendingRespawn>;

	using Spawns = std::vector<GameObjectId>;

	void DoRespawn(const GameObjectId gameObjectId, RespawnComponent* entityRespawnComponent);

private:

	Spawns m_Spawns;

	RespawnQueue m_RespawnQueue;

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	void OnGameObjectCreated(const GameObjectCreated* event);
	void OnGameObjectDestroyed(const GameObjectDestroyed* event);
	void OnGameObjectKilled(const GameObjectKilled* event);

public:

	RespawnSystem();
	virtual ~RespawnSystem();

	virtual void Update(float dt) override;

	void RespawnGameObject(const GameObjectId gameObjectId);

}; // class RespawnSystem

#endif // __RESPAWN_SYSTEM_H__
