///-------------------------------------------------------------------------------------------------
/// File:	OrthoCamera.cpp.
///
/// Summary:	Implements the ortho camera class.
///-------------------------------------------------------------------------------------------------

#include "OrthoCamera.h"

OrthoCamera::OrthoCamera(const glm::vec3& position, const float zoom) :
	m_Zoom(zoom)
{
	this->m_Position = position;
	this->m_Forward = glm::vec3(0.0f, 0.0f, -1.0f);
}

OrthoCamera::~OrthoCamera()
{}

Transform OrthoCamera::GetViewTransform() const
{
	return glm::mat4
	(
		glm::vec4(this->m_Left		, 0.0f),
		glm::vec4(this->m_Up		, 0.0f),
		glm::vec4(this->m_Forward	, 0.0f),
		glm::vec4(this->m_Position	, 1.0f)
	);
}

Transform OrthoCamera::GetProjectionTransform() const
{
	const float scaledHalfWidth = this->m_Viewport.z * 0.5f * this->m_Zoom;
	const float scaledHalfHeight = this->m_Viewport.w * 0.5f * this->m_Zoom;

	return glm::ortho(-scaledHalfWidth, scaledHalfWidth, scaledHalfHeight, -scaledHalfHeight, this->m_Near, this->m_Far);	
}

void OrthoCamera::TurnLeft(const float degrees)
{
	this->m_Up    = glm::rotate(this->m_Up   , degrees, this->m_Forward);
	this->m_Left = glm::rotate(this->m_Left, degrees, this->m_Forward);
}

void OrthoCamera::TurnRight(const float degrees)
{
	this->m_Up    = glm::rotate(this->m_Up   , -degrees, this->m_Forward);
	this->m_Left = glm::rotate(this->m_Left, -degrees, this->m_Forward);
}