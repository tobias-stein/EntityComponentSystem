///-------------------------------------------------------------------------------------------------
/// File:	Shape.h.
///
/// Summary:	Includes all specific shape classes and declares a Shape class which is a sort of
/// handle and can be used to access shape data.
///-------------------------------------------------------------------------------------------------


#ifndef __SHAPE_H__
#define __SHAPE_H__

// Shapes
#include "TriangleShape.h"
#include "QuadShape.h"



class Shape
{
	const IShape* m_ShapeData;

public:


	Shape(const IShape* shapeData);
	~Shape();


	// >>> Forward methods to real shape data >>> 

	inline const size_t				GetVertexCount() const { this->m_ShapeData->GetVertexCount(); }

	inline const float*				GetPosition() const { this->m_ShapeData->GetPosition(); }

	inline const unsigned short*	GetIndex() const { this->m_ShapeData->GetIndex(); }

	inline const float*				GetNormal() const { this->m_ShapeData->GetNormal(); }

	inline const float*				GetUV() const { this->m_ShapeData->GetUV(); }

	inline const float*				GetColor() const { this->m_ShapeData->GetColor(); }

}; // class Shape

#endif // __SHAPE_H__
