///-------------------------------------------------------------------------------------------------
/// File:	ShapeComponent.h.
///
/// Summary:	Declares the shape component class.
///-------------------------------------------------------------------------------------------------

#ifndef __SHAPE_COMPONENT_H__
#define __SHAPE_COMPONENT_H__

#include <ECS.h>

#include "Shape.h"

class ShapeComponent : public Shape, public ECS::Component<ShapeComponent>
{
public:

	ShapeComponent(const Shape& shape);

	virtual ~ShapeComponent();

}; // class ShapeComponent

#endif // __SHAPE_COMPONENT_H__
