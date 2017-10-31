///-------------------------------------------------------------------------------------------------
/// File:	Wall.cpp.
///
/// Summary:	Implements the wall class.
///-------------------------------------------------------------------------------------------------

#include "Wall.h"

#include "RigidbodyComponent.h"
#include "MaterialComponent.h"
#include "ShapeComponent.h"
#include "CollisionComponent2D.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"

Wall::Wall(const glm::vec3& size)
{
	AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	AddComponent<RigidbodyComponent>(0.0f, 1.0f, 1.0f, 1.0f, 10000.0f);

	Shape shape = ShapeGenerator::CreateShape<QuadShape>();
	AddComponent<ShapeComponent>(shape);
	auto cc = AddComponent<CollisionComponent2D>(shape, size, WALL_COLLSION_CATEGORY, WALL_COLLSION);
	cc->isSensor = true;
}

Wall::~Wall()
{
}