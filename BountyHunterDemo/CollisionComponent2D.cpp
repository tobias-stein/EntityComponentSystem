///-------------------------------------------------------------------------------------------------
/// File:	CollisionComponent2D.cpp.
///
/// Summary:	Implements the collision component class.
///-------------------------------------------------------------------------------------------------

#include "CollisionComponent2D.h"

CollisionComponent2D::CollisionComponent2D(const Shape& shape, const glm::vec2& scale, uint16 category, uint16 mask) :
	collisionCategory(category),
	collisionMask(mask)
{
	if (shape.IsValid() == false)
		return;

	switch (shape.GetShapeID())
	{
		case IShape::TRIANLGE:
		{
			this->shapeType = b2Shape::e_polygon;

			static const b2Vec2 VDATA[3] =
			{
				{     0.0f,  scale.y },
				{  scale.x,  scale.y },
				{ -scale.x, -scale.y }
			};

			asPolygonShape.Set(VDATA, 3);
			break;
		}

		case IShape::QUAD:
		{
			this->shapeType = b2Shape::e_polygon;

			this->asPolygonShape.SetAsBox(scale.x, scale.y);
			break;
		}

		default:
			assert(false && "Unsupported collision shape.");
	}
}

CollisionComponent2D::~CollisionComponent2D()
{
}