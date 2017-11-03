///-------------------------------------------------------------------------------------------------
/// File:	WorldSystem.h.
///
/// Summary:	Declares the world system class.
///-------------------------------------------------------------------------------------------------


#ifndef __WORLD_SYSTEM_H__
#define __WORLD_SYSTEM_H__

#include "GameObject.h"

#include "CollisionComponent2D.h"
#include "RigidbodyComponent.h"


// box2d Physics
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"

class WorldSystem : public ECS::System<WorldSystem>
{
	struct SpawnInfo
	{
		GameObjectId 	m_GameObjectID;
		Transform		m_Transform;

		SpawnInfo() :
			m_GameObjectID(INVALID_GAMEOBJECT_ID),
			m_Transform(Transform())
		{}

		SpawnInfo(GameObjectId gameObjectId, const Transform& transform) :
			m_GameObjectID(gameObjectId),
			m_Transform(transform)
		{}

	}; // struct SpawnInfo

	struct WorldObjectInfo
	{
		GameObjectId		m_GameObjectID;
		ECS::EntityTypeId	m_GameObjectType;

		WorldObjectInfo() :
			m_GameObjectID(INVALID_GAMEOBJECT_ID),
			m_GameObjectType(ECS::INVALID_TYPE_ID)
		{}

		WorldObjectInfo(GameObjectId objectId, ECS::EntityTypeId typeId) :
			m_GameObjectID(objectId),
			m_GameObjectType(typeId)
		{}

	}; // struct WorldObjectInfo

	using SpawnQueue	= std::vector<SpawnInfo>;
	using KillQueue		= std::vector<GameObjectId>;

	using WorldObjects	= std::vector<WorldObjectInfo>;

private:

	b2World			m_Box2DWorld;

	WorldObjects	m_WorldObjects;

	SpawnQueue		m_SpawnQueue;
	size_t			m_PendingSpawns;

	KillQueue		m_KillQueue;
	size_t			m_PendingKills;

public:

	WorldSystem();
	virtual ~WorldSystem();

	virtual void PreUpdate(float dt) override;
	virtual void Update(float dt) override;
	virtual void PostUpdate(float dt) override;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual void IWorld::SpawnGameObject(GameObjectId gameObjectId, const Transform& transform) = 0;
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

	void SpawnGameObject(GameObjectId gameObjectId, const Transform& transform);

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual void IWorld::KillGameObject(GameObjectId gameObjectId) = 0;
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

	void KillGameObject(GameObjectId gameObjectId);

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual void IWorld::RemoveGameObject(GameObjectId gameObjectId) = 0;
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

	void RemoveGameObject(GameObjectId gameObjectId);

	///-------------------------------------------------------------------------------------------------
	/// Fn:	void WorldSystem::Clear();
	///
	/// Summary:	Clears the entire world.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	22/10/2017
	///-------------------------------------------------------------------------------------------------

	void Clear();

	template<class T, class... ARGS>
	GameObjectId AddGameObject(Transform transform, ARGS&&... args)
	{
		// create entity
		GameObjectId entityId = ECS::ECS_Engine->GetEntityManager()->CreateEntity<T>(std::forward<ARGS>(args)...);

		ECS::IEntity* gameObject = ECS::ECS_Engine->GetEntityManager()->GetEntity(entityId);

		// get entities transform
		TransformComponent* entityTransformComponent = gameObject->GetComponent<TransformComponent>();
		assert(entityTransformComponent != nullptr && "Failure! Spawned entity has no TransformComponent!");

		// set initial transform
		*entityTransformComponent = transform;

		// add to box2d physics world ...
		{
			RigidbodyComponent* rbComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<RigidbodyComponent>(entityId);
			CollisionComponent2D* coComp = ECS::ECS_Engine->GetComponentManager()->GetComponent<CollisionComponent2D>(entityId);

			if (rbComp != nullptr)
			{
				// Create new rigid body
				b2BodyDef bodyDef;
				{
					bodyDef.type = rbComp->m_Box2DBodyType;
					bodyDef.linearDamping = rbComp->m_LinearDamping;
					bodyDef.angularDamping = rbComp->m_AngularDamping;
				}
				rbComp->m_Box2DBody = this->m_Box2DWorld.CreateBody(&bodyDef);

				// set initial transform
				rbComp->SetTransform(*entityTransformComponent);

				if (coComp != nullptr)
				{
					b2FixtureDef fixtureDef;
					{
						switch (coComp->shapeType)
						{
						case b2Shape::e_circle:
							fixtureDef.shape = &coComp->asCircleShape;
							break;

						case b2Shape::e_polygon:
							fixtureDef.shape = &coComp->asPolygonShape;
							break;

						default:
							assert(false && "Unsupported collision shape!");
						}

						fixtureDef.friction = rbComp->m_Friction;
						fixtureDef.density = rbComp->m_Density;

						fixtureDef.filter.categoryBits = coComp->collisionCategory;
						fixtureDef.filter.maskBits = coComp->collisionMask;

						fixtureDef.isSensor = coComp->isSensor;
					}

					// create new fixture and add reference to its component
					rbComp->m_Box2DBody->CreateFixture(&fixtureDef)->SetUserData(rbComp);
				}
			}
		}

		// add Gameobject to list
		size_t i = 0;
		for (; i < this->m_WorldObjects.size(); ++i)
		{
			if (this->m_WorldObjects[i].m_GameObjectID == INVALID_GAMEOBJECT_ID)
			{
				this->m_WorldObjects[i] = WorldObjectInfo(entityId, gameObject->GetStaticEntityTypeID());
				return entityId;
			}
		}

		this->m_WorldObjects.resize(this->m_WorldObjects.size() * 2);
		this->m_WorldObjects[i] = WorldObjectInfo(entityId, gameObject->GetStaticEntityTypeID());

		return entityId;
	}

	template<class T>
	T* GetGameObject(const GameObjectId& objectId)
	{
		return static_cast<T*>(ECS::ECS_Engine->GetEntityManager()->GetEntity(objectId));
	}

	///-------------------------------------------------------------------------------------------------
	/// Fn:	inline b2World& WorldSystem::GetBox2dWorld()
	///
	/// Summary:	Gets box 2D world.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	3/11/2017
	///
	/// Returns:	The box 2D world.
	///-------------------------------------------------------------------------------------------------

	inline b2World* GetBox2dWorld() { return &this->m_Box2DWorld; }


	///-------------------------------------------------------------------------------------------------
	/// Fn:	template<class T> void WorldSystem::KillAllGameObjects()
	///
	/// Summary:	Kills all game objects of type T.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	13/10/2017
	///
	/// Typeparams:
	/// T - 	Generic type parameter.
	///-------------------------------------------------------------------------------------------------

	template<class T>
	void KillAllGameObjects()
	{
		ECS::EntityTypeId TYPE_ID = T::STATIC_ENTITY_TYPE_ID;

		for (auto wo : this->m_WorldObjects)
			if (wo.m_GameObjectType == TYPE_ID)
				KillGameObject(wo.m_GameObjectID);
	}

	///-------------------------------------------------------------------------------------------------
	/// Fn:	void WorldSystem::KillAllGameObjects()
	///
	/// Summary:	Kill all game objects.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	13/10/2017
	///-------------------------------------------------------------------------------------------------

	void KillAllGameObjects()
	{
		for (auto wo : this->m_WorldObjects)
			KillGameObject(wo.m_GameObjectID);
	}

	void DumpPhysics()
	{
		this->m_Box2DWorld.Dump();
	}

}; // class WorldSystem

#endif // __WORLD_SYSTEM_H__
