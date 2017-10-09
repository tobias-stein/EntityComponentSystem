///-------------------------------------------------------------------------------------------------
/// File:	GameCamera.h.
///
/// Summary:	Declares the main camera class.
///-------------------------------------------------------------------------------------------------

#ifndef __GAME_CAMERA_H__
#define __GAME_CAMERA_H__

#include "GameObject.h"
#include "GameEvents.h"
#include "Camera.h"




class GameCamera : private Camera, public GameObject<GameCamera>, public ECS::Event::IEventListener
{
private:

	bool				m_projectionDirty;
	bool				m_viewDirty;

	Transform			m_ViewTransform;
	Transform			m_ProjectionTransform;

	TransformComponent* m_ThisTransformComponent;

	void RegisterEventCallbacks();
	void UnregisterEventCallbacks();

	void OnWindowResized(const WindowResizedEvent* event);

public:

	template<class... ARGS>
	GameCamera(ARGS&... args) : 
		GameObject(std::forward<ARGS>(args)...),
		m_viewDirty(true),
		m_projectionDirty(true)
	{
		RegisterEventCallbacks();

		this->m_ThisTransformComponent = GetComponent<TransformComponent>();
		ECS::ECS_Engine->SendEvent<CameraCreated>(this->GetEntityID());
	}

	virtual ~GameCamera()
	{
		UnregisterEventCallbacks();
		ECS::ECS_Engine->SendEvent<CameraDestroyed>(this->GetEntityID());
	}

	Transform GetCameraProjectionTransform()
	{
		if (this->m_projectionDirty == true)
		{
			this->m_ProjectionTransform = GetProjectionTransform();
			this->m_projectionDirty = false;
		}

		return this->m_ProjectionTransform;
	}

	Transform GetCameraViewTransform()
	{
		if (this->m_viewDirty == true)
		{
			this->m_ViewTransform = *this->m_ThisTransformComponent = GetCameraViewTransform();
			this->m_viewDirty = false;
		}

		return this->m_ViewTransform;
	}
}; // class GameCamera

#endif // __GAME_CAMERA_H__
