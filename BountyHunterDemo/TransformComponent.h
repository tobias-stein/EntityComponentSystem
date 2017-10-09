///-------------------------------------------------------------------------------------------------
/// File:	TransformComponent.h.
///
/// Summary:	Declares the transform component class.
///-------------------------------------------------------------------------------------------------

#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include <ECS/ECS.h>

#include "Transform.h"

class TransformComponent : public Transform, public ECS::Component<TransformComponent>
{
	
public:

	TransformComponent();
	TransformComponent(const Transform& transform);
	virtual ~TransformComponent();

	inline const float* GetTranformPtr() const { return *this; }

}; // class TransformComponent

#endif // __TRANSFORM_COMPONENT_H__
