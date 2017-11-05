///-------------------------------------------------------------------------------------------------
/// File:	CollisionComponent2D.cpp.
///
/// Summary:	Implements the collision component class.
///-------------------------------------------------------------------------------------------------

#include "CollisionComponent2D.h"

#include "GameConfiguration.h"

CollisionComponent2D::CollisionComponent2D(const Shape& shape, const glm::vec2& scale, uint16 category, uint16 mask) :
	shapeID(shape.GetShapeID()),
	collisionCategory(category),
	collisionMask(mask),
	isSensor(false)
{
	assert(shape.IsValid() != false && "Invalid shape!");
	Rescale(scale);
}

CollisionComponent2D::~CollisionComponent2D()
{
}

void CollisionComponent2D::Rescale(const glm::vec2& scale)
{
	auto S = scale * GLOBAL_SCALE;

	switch (this->shapeID)
	{
		case IShape::TRIANLGE:
		{
			this->shapeType = b2Shape::e_polygon;

			static const b2Vec2 VDATA[3] =
			{
				{ 0.0f,  S.y },
				{ S.x,  S.y },
				{ -S.x, -S.y }
			};

			asPolygonShape.Set(VDATA, 3);
			break;
		}

		case IShape::QUAD:
		{
			this->shapeType = b2Shape::e_polygon;
			this->asPolygonShape.SetAsBox(S.x, S.y);
			break;
		}

		default:
			assert(false && "Unsupported collision shape.");
	}
}
