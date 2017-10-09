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
public:

	enum ProjectionMode
	{
		PerspectiveViewmode = 0,
		OrthogonalViewmode = 1,

		MAX_PROJECTION_MODES
	};

protected:

	ProjectionMode	m_Mode;

	float			m_fov;
	float			m_aspect;

	float			m_Near;
	float			m_Far;

	float			m_zoom;

	glm::vec3		m_Position;
	glm::vec3		m_LookAt;
	glm::vec3		m_Up;

	glm::uvec4		m_Viewport;

public:

	Camera();
	Camera(const glm::vec3& eye, const glm::vec3& target = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));

	virtual ~Camera();

	Transform GetViewTransform();
	Transform GetProjectionTransform();

	inline void SetPerspectiveViewmode() { this->m_Mode = PerspectiveViewmode; }
	inline void SetOrthogonalViewmode() { this->m_Mode = OrthogonalViewmode; }

	inline ProjectionMode GetProjectionMode() const { return this->m_Mode; }

	inline void SetFov(const float fov) { this->m_fov = fov; }
	inline float GetFov() const { return this->m_fov; }

	//inline void SetNearPlane(const float near) { this->m_Near = near; }
	//inline float GetNearPlane() const { return this->m_Near; }

	//inline void SetFarPlane(const float far) { this->m_Far = far; }
	//inline float GetFarPlane() const { return this->m_Far; }

	inline void SetZoom(const float zoom) { this->m_zoom = 1.0f / zoom; }
	inline float GetZoom() const { return this->m_zoom; }

	inline void SetViewport(const glm::uvec4& viewport) { this->m_Viewport = viewport; }
	inline void SetViewport(const unsigned int x, const unsigned int y, const unsigned int w, const unsigned int h) { this->m_Viewport = glm::uvec4(x, y, w, h); }
	inline glm::uvec4 GetViewport() const { return this->m_Viewport; }

}; // class Camera

#endif // __CAMERA_H__