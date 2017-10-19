///-------------------------------------------------------------------------------------------------
/// File:	IWorld.h.
///
/// Summary:	Interface class for concrete world class implementations.
///-------------------------------------------------------------------------------------------------


#ifndef __I_WORLD_H__
#define __I_WORLD_H__

#include <ECS/ECS.h>

#include "GameTypes.h"
#include "Bounds.h"



using GameObjectQuery = std::vector<ECS::EntityId>;

///-------------------------------------------------------------------------------------------------
/// Class:	IWorld
///
/// Summary:	A virtual world that contains game objects. A world object provides elementry functions
/// for adding and removing game objects as well as getting all game objects in a certain query range.
///
/// Author:	Tobias Stein
///
/// Date:	12/10/2017
///-------------------------------------------------------------------------------------------------

class IWorld
{
protected:

	const Bounds		m_WorldBounds;

	const glm::vec3		m_WorldUp;

public:

	IWorld(const Bounds& worldBounds, const glm::vec3& worldUp = glm::vec3(0.0f, 1.0f, 0.0f)) :
		m_WorldBounds(worldBounds),
		m_WorldUp(worldUp)
	{}

	virtual ~IWorld()
	{}

	///-------------------------------------------------------------------------------------------------
	/// Fn:	inline const Bounds& IWorld::GetWorldBounds() const
	///
	/// Summary:	Gets world bounds.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	12/10/2017
	///
	/// Returns:	The world bounds.
	///-------------------------------------------------------------------------------------------------

	inline const Bounds&			GetWorldBounds() const { return this->m_WorldBounds; }

	///-------------------------------------------------------------------------------------------------
	/// Fn:	inline const glm::vec3 IWorld::GetWorldUpVector() const
	///
	/// Summary:	Gets world up vector.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	12/10/2017
	///
	/// Returns:	The world up vector.
	///-------------------------------------------------------------------------------------------------

	inline const glm::vec3&			GetWorldUp() const { return this->m_WorldUp; }

	virtual void Update(float dt) = 0;

	virtual void AddGameObject(GameObjectId gameObjectId) = 0;

	virtual void RemoveGameObject(GameObjectId gameObjectId) = 0;

}; // class IWorld

#endif // __I_WORLD_H__
