///-------------------------------------------------------------------------------------------------
/// File:	TransformComponent.cpp.
///
/// Summary:	Implements the transform component class.
///-------------------------------------------------------------------------------------------------

#include "TransformComponent.h"

TransformComponent::TransformComponent()
{}

TransformComponent::TransformComponent(const glm::mat4& transform) : m_Transform(transform)
{}

TransformComponent::TransformComponent(const Transform& transform) : m_Transform(transform)
{}

TransformComponent::~TransformComponent()
{}
