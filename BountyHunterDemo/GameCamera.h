///-------------------------------------------------------------------------------------------------
/// File:	GameCamera.h.
///
/// Summary:	Declares the main camera class.
///-------------------------------------------------------------------------------------------------

#ifndef __GAME_CAMERA_H__
#define __GAME_CAMERA_H__

#include "GameObject.h"
#include "GameEvents.h"

#include "OrthoCamera.h"


class IGameCamera
{
public:

	virtual ~IGameCamera()
	{}

	virtual ECS::EntityId GetCameraID() const = 0;

	virtual Transform GetProjectionTransform() = 0;

	virtual Transform GetViewTransform() = 0;

}; // IGameCamera

template<class C>
class GameCamera : public IGameCamera, public GameObject<Camera>, public ECS::Event::IEventListener
{
private:

	Transform			m_ViewTransform;
	Transform			m_ProjectionTransform;

	TransformComponent* m_ThisTransformComponent;

	void OnWindowResized(const WindowResizedEvent* event)
	{
		this->m_Camera->SetViewport(glm::uvec4(0, 0, event->width, event->height));
	}

protected:

	C*					m_Camera;

	bool				m_projectionDirty;
	bool				m_viewDirty;


public:

	template<class... ARGS>
	GameCamera(ARGS&... args) :
		m_Camera(new C(std::forward<ARGS>(args)...)),
		m_viewDirty(true),
		m_projectionDirty(true),
		m_ThisTransformComponent(nullptr)
	{
		RegisterEventCallback(&GameCamera::OnWindowResized);

		this->m_ThisTransformComponent = GetComponent<TransformComponent>();
		ECS::ECS_Engine->SendEvent<CameraCreated>(this->GetEntityID());
	}

	virtual ~GameCamera()
	{
		UnregisterEventCallback(&GameCamera::OnWindowResized);

		ECS::ECS_Engine->SendEvent<CameraDestroyed>(this->GetEntityID());

		delete this->m_Camera;
		this->m_Camera = nullptr;
	}

	virtual ECS::EntityId GetCameraID() const override { return this->m_EntityID; }

	virtual Transform GetProjectionTransform() override
	{
		if (this->m_projectionDirty == true)
		{
			this->m_ProjectionTransform = this->m_Camera->GetProjectionTransform();
			this->m_projectionDirty = false;
		}

		return this->m_ProjectionTransform;
	}

	virtual Transform GetViewTransform() override
	{
		if (this->m_viewDirty == true)
		{
			this->m_ViewTransform = *this->m_ThisTransformComponent = this->m_Camera->GetViewTransform();
			this->m_viewDirty = false;
		}

		return this->m_ViewTransform;
	}

	inline void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
	{
		this->m_Camera->SetViewport(glm::uvec4(x, y, w, h));
	}

}; // class GameCamera

#endif // __GAME_CAMERA_H__
