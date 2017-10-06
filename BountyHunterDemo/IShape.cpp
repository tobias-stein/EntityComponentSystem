///-------------------------------------------------------------------------------------------------
/// File:	IShape.cpp.
///
/// Summary:	Declares the IShape interface.
///-------------------------------------------------------------------------------------------------


#include "IShape.h"

unsigned long IShape::NEXT_STATIC_SHAPE_ID { 0u };

IShape::IShape()
{
	this->Initialize();
}

IShape::~IShape()
{
	this->Release();
}