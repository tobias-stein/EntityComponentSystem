///-------------------------------------------------------------------------------------------------
/// File:	Collector.cpp.
///
/// Summary:	Implements the collector class.
///-------------------------------------------------------------------------------------------------

#include "Collector.h"

#include "ShapeComponent.h"
#include "MaterialComponent.h"
#include "RespawnComponent.h"

#include "ShapeGenerator.h"
#include "MaterialGenerator.h"

Collector::Collector(GameObjectId spawnId)
{
	AddComponent<ShapeComponent>(ShapeGenerator::CreateShape<TriangleShape>());
	AddComponent<MaterialComponent>(MaterialGenerator::CreateMaterial<DefaultMaterial>());
	AddComponent<RespawnComponent>(COLLECTOR_RESPAWNTIME, spawnId, true);

	this->m_ThisTransform = GetComponent<TransformComponent>();
	assert(this->m_ThisTransform != nullptr && "Failed to get transform");
}

Collector::~Collector()
{}

void Collector::MoveForward(float speed)
{
	*this->m_ThisTransform = glm::translate(glm::mat4(1.0f), this->m_ThisTransform->GetUp() * speed) * this->m_ThisTransform->AsMat4();
}

void Collector::TurnLeft(float degrees)
{
	*this->m_ThisTransform = glm::rotate(this->m_ThisTransform->AsMat4(), degrees, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Collector::TurnRight(float degrees)
{
	*this->m_ThisTransform = glm::rotate(this->m_ThisTransform->AsMat4(), -degrees, glm::vec3(0.0f, 0.0f, 1.0f));
}
