///-------------------------------------------------------------------------------------------------
/// File:	TriangleShape.h.
///
/// Summary:	Declares the triangle shape class.
///-------------------------------------------------------------------------------------------------

#ifndef __TRIANGLE_SHAPE__
#define __TRIANGLE_SHAPE__

#include "IShape.h"

class TriangleShape : public IShape
{
private:

	static constexpr size_t				VERTEX_COUNT { 3 };

	static constexpr size_t				TRIANGLE_COUNT { 1 };

	static constexpr size_t				INDEX_COUNT { 3 };

	static constexpr VertexPositionData	VERTEX_DATA_POS[VERTEX_COUNT * VERTEX_POSITION_DATA_ELEMENT_LEN]
	{
		//	x,		y,		z
		-1.0f,	-1.0f,	0.0f,			// v0
		 0.0f,	 1.0f,	0.0f,			// v1
		 1.0f,	-1.0f,	0.0f,			// v2

	};

	static constexpr VertexNormalData	VERTEX_DATA_NRM[VERTEX_COUNT * VERTEX_NORMAL_DATA_ELEMENT_LEN]
	{
		//	x,		y,		z
		0.0f,	 1.0f,	0.0f,			// n0
		0.0f,	 1.0f,	0.0f,			// n1
		0.0f,	 1.0f,	0.0f,			// n2
	};

	static constexpr VertexIndexData	VERTEX_DATA_IDX[INDEX_COUNT]
	{
		0, 1, 2
	};

public:

	static constexpr Type				SHAPE_TYPE { TRIANLGE };

	TriangleShape()
	{}

	virtual ~TriangleShape()
	{}

	virtual inline ShapeID				GetShapeID() const override { return SHAPE_TYPE; }

	virtual bool						Initialize() const override { return true; }

	virtual void						Release() const override { }

	virtual const size_t				GetVertexCount() const override { return VERTEX_COUNT; }

	virtual const size_t				GetTriangleCount() const override { return TRIANGLE_COUNT; }

	virtual const size_t				GetIndexCount() const override { return INDEX_COUNT; }
	
	virtual const VertexPositionData*	GetPosition() const override { return VERTEX_DATA_POS; }

	virtual const VertexIndexData*		GetIndex() const override { return VERTEX_DATA_IDX; }

	virtual const VertexNormalData*		GetNormal() const override { return VERTEX_DATA_NRM; }

	virtual const VertexTexCoordData*	GetTexCoord() const override { return nullptr; }

	virtual const VertexColorData*		GetColor() const override { return nullptr; }

}; // class TriangleShape

#endif // __TRIANGLE_SHAPE__
