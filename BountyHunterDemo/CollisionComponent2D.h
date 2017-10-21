///-------------------------------------------------------------------------------------------------
/// File:	CollisionComponent2D.h.
///
/// Summary:	Declares the collision component class.
///-------------------------------------------------------------------------------------------------

#ifndef __COLLISION_COMPONENT_2D_H__
#define __COLLISION_COMPONENT_2D_H__

#include <ECS/ECS.h>

#include "math.h"

#include "Shape.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"


class CollisionComponent2D : public ECS::Component<CollisionComponent2D>
{
public:

	b2Shape::Type		shapeType;

	b2CircleShape		asCircleShape;
	b2PolygonShape		asPolygonShape;

	uint16				collisionCategory;
	uint16				collisionMask;

	CollisionComponent2D(const Shape& shape, const glm::vec2& scale = glm::vec2(1.0f), uint16 category = 0x0001, uint16 mask = 0xffff);
	virtual ~CollisionComponent2D();

}; // class CollisionComponent

#endif // __COLLISION_COMPONENT_2D_H__
