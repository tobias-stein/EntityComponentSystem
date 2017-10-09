///-------------------------------------------------------------------------------------------------
/// File:	ShapeComponent.cpp.
///
/// Summary:	Implements the shape component class.
///-------------------------------------------------------------------------------------------------

#include "ShapeComponent.h"

ShapeComponent::ShapeComponent(const Shape& shape) : Shape(shape)
{}

ShapeComponent::~ShapeComponent()
{}

void ShapeComponent::SetShapeBufferIndex(const ShapeBufferIndex& shapeBufferIndex)
{
	this->m_PositionDataIndex	= shapeBufferIndex.GetPositionDataIndex();
	this->m_IndexDataIndex		= shapeBufferIndex.GetIndexDataIndex();
	this->m_NormalDataIndex		= shapeBufferIndex.GetNormalDataIndex();
	this->m_TexCoordDataIndex	= shapeBufferIndex.GetTexCoordDataIndex();
	this->m_ColorDataIndex		= shapeBufferIndex.GetColorDataIndex();
}
