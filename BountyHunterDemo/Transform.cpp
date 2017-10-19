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

Transform::Transform(const glm::vec3& position, const glm::vec3 axis, const float angle_radians)
{
	glm::mat4 P			= glm::translate(glm::mat4(1.0f), position);
	glm::mat4 PR		= glm::rotate(P, angle_radians, axis);

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

Transform::Transform(const glm::vec3& position, const glm::vec3 axis, const float angle_radians, const glm::vec3& scale)
{
	glm::mat4 P			= glm::translate(glm::mat4(1.0f), position);
	glm::mat4 PR		= glm::rotate(P, angle_radians, axis);
	glm::mat4 PRS		= glm::scale(PR, scale);

	this->m_Transform	= PRS;
}

void Transform::SetPosition(const glm::vec3 & position)
{
	this->m_Transform[3] = glm::vec4(position, this->m_Transform[3].w);
}

void Transform::SetRotation(const glm::vec3 & rotation_euler_radians)
{
	glm::vec3 Tr = this->GetPosition();
	glm::vec3 Sc = this->GetScale();

	auto T = glm::translate(glm::mat4(1.0f), Tr);
	auto R = glm::yawPitchRoll(rotation_euler_radians.x, rotation_euler_radians.y, rotation_euler_radians.z);

	this->m_Transform = T * R * glm::scale(Sc);
}

void Transform::SetScale(const glm::vec3& scale)
{
	glm::vec3 Tr = this->GetPosition();
	glm::vec3 Or = this->GetRotation();

	auto T = glm::translate(glm::mat4(1.0f), Tr);
	auto R = glm::yawPitchRoll(Or.x, Or.y, Or.z);

	this->m_Transform = T * R * glm::scale(scale);
}

glm::vec3 Transform::GetRotation() const
{
	glm::vec3 euler_angles;
	glm::extractEulerAngleXYZ(this->m_Transform, euler_angles[0], euler_angles[1], euler_angles[2]);

	return euler_angles;
}

glm::vec3 Transform::GetScale() const
{
	glm::vec3 row[3];
	for (size_t i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			row[i][j] = this->m_Transform[i][j];
	
	return glm::vec3(glm::length(row[0]), glm::length(row[1]), glm::length(row[1]));
}
