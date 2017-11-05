///-------------------------------------------------------------------------------------------------
/// File:	TransformComponent.h.
///
/// Summary:	Declares the transform component class.
///-------------------------------------------------------------------------------------------------

#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include <ECS/ECS.h>

#include "Transform.h"

class TransformComponent : public ECS::Component<TransformComponent>
{
private:

	Transform	m_Transform;

public:

	TransformComponent();
	TransformComponent(const glm::mat4& transform);
	TransformComponent(const Transform& transform);

	virtual ~TransformComponent();


	inline void SetTransform(const glm::mat4& transform) { this->m_Transform = transform; }

	inline Transform* AsTransform() { return &(this->m_Transform); }

	inline const float*		AsFloat() const { return this->m_Transform; }
	inline const glm::mat4& AsMat4() const { return this->m_Transform; }

}; // class TransformComponent

#endif // __TRANSFORM_COMPONENT_H__
