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
private:

	const IShape* m_ShapeData;

public:


	Shape(const IShape* shapeData);
	~Shape();

	inline const ShapeID				GetShapeID() const { return this->m_ShapeData->GetShapeID(); }

	// >>> Forward methods to real shape data >>> 

	inline const size_t					GetVertexCount() const { return this->m_ShapeData->GetVertexCount(); }

	inline const size_t					GetTriangleCount() const { return this->m_ShapeData->GetTriangleCount(); }

	inline const size_t					GetIndexCount() const { return this->m_ShapeData->GetIndexCount(); }

	inline const bool					IsIndexed() const { return this->m_ShapeData->GetIndex() != nullptr; }

	inline const VertexPositionData*	GetPosition() const { return this->m_ShapeData->GetPosition(); }

	inline const VertexIndexData*		GetIndex() const { return this->m_ShapeData->GetIndex(); }

	inline const VertexNormalData*		GetNormal() const { return this->m_ShapeData->GetNormal(); }

	inline const VertexTexCoordData*	GetTexCoord() const { return this->m_ShapeData->GetTexCoord(); }

	inline const VertexColorData*		GetColor() const { return this->m_ShapeData->GetColor(); }

}; // class Shape

#endif // __SHAPE_H__
