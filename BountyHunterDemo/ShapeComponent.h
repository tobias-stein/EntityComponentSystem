///-------------------------------------------------------------------------------------------------
/// File:	ShapeComponent.h.
///
/// Summary:	Declares the shape component class.
///-------------------------------------------------------------------------------------------------

#ifndef __SHAPE_COMPONENT_H__
#define __SHAPE_COMPONENT_H__

#include <ECS.h>

#include "Shape.h"
#include "ShapeBufferIndex.h"

class ShapeComponent : public Shape, public ShapeBufferIndex, public ECS::Component<ShapeComponent>
{
	friend class RenderSystem;

	void SetShapeBufferIndex(const ShapeBufferIndex& shapeBufferIndex);

public:

	ShapeComponent(const Shape& shape);

	virtual ~ShapeComponent();

}; // class ShapeComponent

#endif // __SHAPE_COMPONENT_H__
