///-------------------------------------------------------------------------------------------------
/// File:	OrthoCamera.h.
///
/// Summary:	Declares the ortho camera class. An orthogonal camera looks alway at the xy-plane.
/// in +z direction,
///-------------------------------------------------------------------------------------------------

#ifndef __ORTHO_CAMERA_H__
#define __ORTHO_CAMERA_H__

#include "Camera.h"

class OrthoCamera : public Camera
{
private:
	
	float m_Zoom;

public:

	OrthoCamera(const glm::vec3& position, const float zoom = 1.0f);
	virtual ~OrthoCamera();

	virtual Transform GetViewTransform() const override;
	virtual Transform GetProjectionTransform() const override;

	void TurnLeft(const float degrees);
	void TurnRight(const float degrees);

	inline void SetZoom(const float zoom)
	{
		assert(zoom > 0.0f && "Camera zoom must be greater zero!");
		this->m_Zoom = 1.0f / zoom;
	}

}; // class OrthoCamera

#endif // __ORTHO_CAMERA_H__
