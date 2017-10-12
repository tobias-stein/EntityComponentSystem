///-------------------------------------------------------------------------------------------------
/// File:	World2D.cpp.
///
/// Summary:	Implements the world 2D class.
///-------------------------------------------------------------------------------------------------

#include "World2D.h"

World2D::World2D(const Bounds2D& worldBounds, const glm::vec2& worldUp) :
	IWorld(Bounds(Point(worldBounds.minBound, 0.0f), Point(worldBounds.maxBound, 0.0f)), Point(worldUp, 0.0f))
{}

World2D::~World2D()
{}

