///-------------------------------------------------------------------------------------------------
/// File:	ShapeGenerator.cpp.
///
/// Summary:	Implements the shape generator class.
///-------------------------------------------------------------------------------------------------


#include "ShapeGenerator.h"
#include "Shape.h"


ShapeGenerator::ShapeGenerator() :
	m_ShapeRegistry(IShape::MAX_SHAPES, nullptr)
{}

ShapeGenerator::~ShapeGenerator()
{
	for (int i = 0; i < this->m_ShapeRegistry.size(); ++i)
	{
		if (this->m_ShapeRegistry[i] != nullptr)
		{
			this->m_ShapeRegistry[i]->Release();
			delete this->m_ShapeRegistry[i];
			this->m_ShapeRegistry[i] = nullptr;
		}
	}
}
