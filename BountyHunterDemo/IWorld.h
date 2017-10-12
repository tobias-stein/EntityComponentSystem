///-------------------------------------------------------------------------------------------------
/// File:	IWorld.h.
///
/// Summary:	Interface class for concrete world class implementations.
///-------------------------------------------------------------------------------------------------


#ifndef __I_WORLD_H__
#define __I_WORLD_H__

#include <ECS/ECS.h>

#include "math.h"


typedef glm::vec3 Point;
typedef glm::vec3 Position;


/// Summary:	Defines an inavlid position.
static const Position INAVLID_POSITION = glm::vec3(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());

struct Bounds
{
	Point minBound;
	Point maxBound;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	Bounds(const Point& boundMin, const Point& boundMax)
	///
	/// Summary:	Contruct bound from min and max point.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	12/10/2017
	///
	/// Parameters:
	/// boundMin - 	The bound minimum.
	/// boundMax - 	The bound maximum.
	///-------------------------------------------------------------------------------------------------

	Bounds(const Point& boundMin, const Point& boundMax) :
		minBound(boundMin),
		maxBound(boundMax)
	{}

	///-------------------------------------------------------------------------------------------------
	/// Fn:	Bounds(const Point& boundCenter, const float radius)
	///
	/// Summary:	Construct bounds from center point and radius
	///
	/// Author:	Tobias Stein
	///
	/// Date:	12/10/2017
	///
	/// Parameters:
	/// boundCenter - 	The bound center.
	/// radius - 	  	The radius.
	///-------------------------------------------------------------------------------------------------

	Bounds(const Point& boundCenter, const float radius) :
		minBound(boundCenter.x - radius, boundCenter.y - radius, boundCenter.z - radius),
		maxBound(boundCenter.x + radius, boundCenter.y + radius, boundCenter.z + radius)
	{}

	///-------------------------------------------------------------------------------------------------
	/// Fn:	inline const bool contains(const Point& point) const
	///
	/// Summary:	Determines if a given point is contained by this bound
	///
	/// Author:	Tobias Stein
	///
	/// Date:	12/10/2017
	///
	/// Parameters:
	/// point - 	The const Point&amp; to test for containment.
	///
	/// Returns:	A const bool.
	///-------------------------------------------------------------------------------------------------

	inline const bool contains(const Point& point) const
	{
		return (this->minBound.x < point.x && point.x < this->maxBound.x) && (this->minBound.y < point.y && point.y < this->maxBound.y) && (this->minBound.z < point.z && point.z < this->maxBound.z);
	}

}; // struct Bounds


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

}; // class IWorld

#endif // __I_WORLD_H__
