///-------------------------------------------------------------------------------------------------
/// File:	TabletopCamera.cpp.
///
/// Summary:	Implements the tabletop camera class.
///-------------------------------------------------------------------------------------------------

#include "TabletopCamera.h"

TabletopCamera::TabletopCamera(const glm::vec2& position, const float zOffset, const float zoom) :
	GameCamera(glm::vec3(position, zOffset))
{
	this->m_Camera->SetZoom(zoom);
}

TabletopCamera::~TabletopCamera()
{}