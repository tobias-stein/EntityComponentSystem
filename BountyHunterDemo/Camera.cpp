///-------------------------------------------------------------------------------------------------
/// File:	Camera.cpp.
///
/// Summary:	Implements the camera class.
///-------------------------------------------------------------------------------------------------

#include "Camera.h"

Camera::Camera() :
	m_Near(0.01f),
	m_Far(100.0f),
	m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_Left(glm::vec3(1.0f, 0.0f, 0.0f)),
	m_Up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_Forward(glm::vec3(0.0f, 0.0f, 1.0f)),
	m_Viewport(0.0f, 0.0f, 1.0f, 1.0f)
{}

Camera::~Camera()
{}