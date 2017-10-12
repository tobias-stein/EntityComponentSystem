///-------------------------------------------------------------------------------------------------
/// File:	Transform.cpp.
///
/// Summary:	Implements the transform class.
///-------------------------------------------------------------------------------------------------

#include "Transform.h"


Transform::Transform() :
	m_Transform(1.0f)
{}

Transform::Transform(const glm::mat4& transform) :
	m_Transform(transform)
{}

Transform::Transform(const glm::vec3& position)
{
	this->m_Transform	= glm::translate(glm::mat4(1.0f), position);
}

Transform::Transform(const glm::vec2& position_xy)
{
	this->m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(position_xy, 0.0f));
}

Transform::Transform(const glm::vec3& position, const glm::quat rotation)
{
	glm::mat4 P			= glm::translate(glm::mat4(1.0f), position);
	glm::mat4 R			= glm::toMat4(rotation);

	this->m_Transform	= P * R;
}

Transform::Transform(const glm::vec3& position, const glm::vec3 axis, const float angle)
{
	glm::mat4 P			= glm::translate(glm::mat4(1.0f), position);
	glm::mat4 PR		= glm::rotate(P, angle, axis);

	this->m_Transform	= PR;
}

Transform::Transform(const glm::vec3& position, const glm::quat rotation, const glm::vec3& scale)
{
	glm::mat4 P			= glm::translate(glm::mat4(1.0f), position);
	glm::mat4 R			= glm::toMat4(rotation);
	glm::mat4 PR		= P * R;
	glm::mat4 PRS		= glm::scale(PR, scale);

	this->m_Transform	= PRS;
}

Transform::Transform(const glm::vec3& position, const glm::vec3 axis, const float angle, const glm::vec3& scale)
{
	glm::mat4 P			= glm::translate(glm::mat4(1.0f), position);
	glm::mat4 PR		= glm::rotate(P, angle, axis);
	glm::mat4 PRS		= glm::scale(PR, scale);

	this->m_Transform	= PRS;
}