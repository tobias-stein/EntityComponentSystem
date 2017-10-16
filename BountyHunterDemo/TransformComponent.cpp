///-------------------------------------------------------------------------------------------------
/// File:	TransformComponent.cpp.
///
/// Summary:	Implements the transform component class.
///-------------------------------------------------------------------------------------------------

#include "TransformComponent.h"

TransformComponent::TransformComponent()
{}

TransformComponent::TransformComponent(const glm::mat4 & transform) : Transform(transform)
{}

TransformComponent::TransformComponent(const Transform& transform) : Transform(transform)
{}

TransformComponent::~TransformComponent()
{}