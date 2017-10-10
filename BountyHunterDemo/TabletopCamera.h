///-------------------------------------------------------------------------------------------------
/// File:	TabletopCamera.h.
///
/// Summary:	Declares the tabletop camera class. A tabletop camera is an orthogonal camera 
/// looking from above vertically down onto the scene.
///-------------------------------------------------------------------------------------------------

#ifndef __TABLE_TOP_CAMERA_H__
#define __TABLE_TOP_CAMERA_H__

#include "GameCamera.h"

class TabletopCamera : public GameCamera<OrthoCamera>
{
public:

	TabletopCamera(const glm::vec2& position, const float zOffset, const float zoom = 1.0f);
	virtual ~TabletopCamera();


}; // class TabletopCamera

#endif // __TABLE_TOP_CAMERA_H__
