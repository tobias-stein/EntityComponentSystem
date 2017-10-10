///-------------------------------------------------------------------------------------------------
/// File:	Camera.h.
///
/// Summary:	Declares the camera class.
///-------------------------------------------------------------------------------------------------

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Transform.h"

class Camera
{
protected:

	float			m_Near;
	float			m_Far;

	glm::vec3		m_Position;
	
	glm::vec3		m_Left;
	glm::vec3		m_Up;
	glm::vec3		m_Forward;
	

	glm::uvec4		m_Viewport;

public:

	Camera();
	virtual ~Camera();

	virtual Transform GetViewTransform() const = 0;
	virtual Transform GetProjectionTransform() const = 0;

	//inline void SetNearPlane(const float near) { this->m_Near = near; }
	//inline void SetFarPlane(const float far) { this->m_Far = far; }

	inline void SetPosition(const glm::vec3& position) { this->m_Position = position; }
	inline void SetViewport(const glm::uvec4& viewport) { this->m_Viewport = viewport; }

}; // class Camera

#endif // __CAMERA_H__