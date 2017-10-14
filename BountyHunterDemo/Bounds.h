///-------------------------------------------------------------------------------------------------
/// File:	Bounds.h.
///
/// Summary:	Declares the bounds class.
///-------------------------------------------------------------------------------------------------

#ifndef __BOUNDS_H__
#define __BOUNDS_H__

#include "math.h"

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


#endif // __BOUNDS_H__
