///-------------------------------------------------------------------------------------------------
/// File:	Shape.cpp.
///
/// Summary:	Implements the shape class.
///-------------------------------------------------------------------------------------------------

#include "Shape.h"

Shape::Shape(const IShape* shapeData) :
	m_ShapeData(shapeData)
{}

Shape::~Shape()
{
	this->m_ShapeData = nullptr;
}