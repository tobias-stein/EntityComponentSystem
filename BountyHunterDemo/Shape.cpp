///-------------------------------------------------------------------------------------------------
/// File:	Shape.cpp.
///
/// Summary:	Implements the shape class.
///-------------------------------------------------------------------------------------------------

#include "Shape.h"

Shape::Shape(const IShape* shapeData) :
	m_ShapeImpl(shapeData)
{}

Shape::~Shape()
{
	this->m_ShapeImpl = nullptr;
}