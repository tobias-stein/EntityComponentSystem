///-------------------------------------------------------------------------------------------------
/// File:	World2D.h.
///
/// Summary:	Declares the world 2D.
///-------------------------------------------------------------------------------------------------

#ifndef __WORLD_2D_H__
#define __WORLD_2D_H__

#include "IWorld.h"



typedef glm::vec2 Point2D;
typedef glm::vec2 Position2D;


struct Bounds2D
{
	Point2D minBound;
	Point2D maxBound;

	Bounds2D(const Bounds& bounds) :
		minBound(bounds.minBound),
		maxBound(bounds.maxBound)
	{}

	Bounds2D(const Point2D& boundMin, const Point2D& boundMax) :
		minBound(boundMin),
		maxBound(boundMax)
	{}

	Bounds2D(const Point2D& boundCenter, const float radius) :
		minBound(boundCenter.x - radius, boundCenter.y - radius),
		maxBound(boundCenter.x + radius, boundCenter.y + radius)
	{}

	Bounds2D(const Point& boundMin, const Point& boundMax) :
		minBound(boundMin),
		maxBound(boundMax)
	{}

	Bounds2D(const Point& boundCenter, const float radius) :
		minBound(boundCenter.x - radius, boundCenter.y - radius),
		maxBound(boundCenter.x + radius, boundCenter.y + radius)
	{}


	inline const bool contains(const Point2D& point) const
	{
		return (this->minBound.x < point.x && point.x < this->maxBound.x) && (this->minBound.y < point.y && point.y < this->maxBound.y);
	}

	inline const bool contains(const Point& point) const
	{
		return (this->minBound.x < point.x && point.x < this->maxBound.x) && (this->minBound.y < point.y && point.y < this->maxBound.y);
	}


}; // struct Bounds2D


///-------------------------------------------------------------------------------------------------
/// Class:	World2D
///
/// Summary:	A 2D world. This world only cares about x and y coordinates.
///
/// Author:	Tobias Stein
///
/// Date:	12/10/2017
///-------------------------------------------------------------------------------------------------

class World2D : public IWorld
{
public:

	World2D(const Bounds2D& worldBounds, const glm::vec2& worldUp = glm::vec2(0.0f, 1.0f));
	virtual ~World2D();

}; // class World2D

#endif // __WORLD_2D_H__
