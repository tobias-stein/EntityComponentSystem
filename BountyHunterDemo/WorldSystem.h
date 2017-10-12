///-------------------------------------------------------------------------------------------------
/// File:	WorldSystem.h.
///
/// Summary:	Declares the world system class.
///-------------------------------------------------------------------------------------------------


#ifndef __WORLD_SYSTEM_H__
#define __WORLD_SYSTEM_H__

#include "World2D.h"
#include "GameObject.h"

/// Summary:	Defines an inavlid position.
static const Point INAVLID_POSITION = glm::vec3(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());

class WorldSystem : public ECS::System<WorldSystem>
{
	struct SpawnInfo
	{
		ECS::EntityId		m_EntityID;
		Transform			m_Transform;

		SpawnInfo() :
			m_EntityID(ECS::INVALID_ENTITY_ID),
			m_Transform(Transform())
		{}

		SpawnInfo(const ECS::EntityId& entityId, const Transform& transform) :
			m_EntityID(entityId),
			m_Transform(transform)
		{}
	};

	using SpawnQueue = std::vector<SpawnInfo>;
	using KillQueue = std::vector<ECS::EntityId>;

private:

	IWorld*		m_World;

	SpawnQueue	m_SpawnQueue;
	size_t		m_PendingSpawns;

	KillQueue	m_KillQueue;
	size_t		m_PendingKills;

public:

	WorldSystem(IWorld* world);
	virtual ~WorldSystem();

	virtual void PreUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void PostUpdate(float dt) override;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual void IWorld::SpawnGameObject(ECS::EntityId entityID, const Transform& transform) = 0;
	///
	/// Summary:	Spawns a game object in the world, if the game object is not yet part of this world
	/// it will be added first. A GameObjectSpawned event will be raised.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	12/10/2017
	///
	/// Parameters:
	/// entityID - 	Identifier for the entity.
	///-------------------------------------------------------------------------------------------------

	void SpawnGameObject(ECS::EntityId entityID, const Transform& transform);

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual void IWorld::KillGameObject(ECS::EntityId entityID) = 0;
	///
	/// Summary:	Kills a game object. This won't remove it from the world, but will mark it as dead.
	/// "Dead" game objects are simply disabled entities. A GameObjectKilled event will be raised.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	12/10/2017
	///
	/// Parameters:
	/// entityID - 	Identifier for the entity.
	///-------------------------------------------------------------------------------------------------

	void KillGameObject(ECS::EntityId entityID);

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual void IWorld::RemoveGameObject(ECS::EntityId entityID) = 0;
	///
	/// Summary:	Removes a game object from the world.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	12/10/2017
	///
	/// Parameters:
	/// entityID - 	Identifier for the entity.
	///-------------------------------------------------------------------------------------------------

	void RemoveGameObject(ECS::EntityId entityID);


	template<class T, class... ARGS>
	void SpawnGameObject(Transform transform, ARGS&&... args)
	{
		// create entity
		ECS::EntityId entityId = ECS::ECS_Engine->GetEntityManager()->CreateEntity<T>(std::forward<ARGS>(args)...);

		// get entities transform
		TransformComponent* entityTransformComponent = ECS::ECS_Engine->GetComponentManager()->GetComponent<TransformComponent>(entityId);
		assert(entityTransformComponent != nullptr && "Failure! Spawned entity has no TransformComponent!");

		// set initial transform
		*entityTransformComponent = transform;
	}

}; // class WorldSystem

#endif // __WORLD_SYSTEM_H__
