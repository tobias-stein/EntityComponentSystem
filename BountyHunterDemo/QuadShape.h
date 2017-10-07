///-------------------------------------------------------------------------------------------------
/// File:	QuadShape.h.
///
/// Summary:	Declares the quad shape class.
///-------------------------------------------------------------------------------------------------

#ifndef __QUAD_SHAPE__
#define __QUAD_SHAPE__

#include "IShape.h"

class QuadShape : public IShape
{
private:

	static constexpr size_t				VERTEX_COUNT { 4 };

	static constexpr size_t				INDEX_COUNT { 6 };

	static constexpr VertexPositionData	VERTEX_DATA_POS[VERTEX_COUNT * SHAPE_VERTEX_POSITION_DATA_ELEMENT_LEN]
	{
		//	x,		y,		z
		-1.0f,	-1.0f,	0.0f,			// v0
		-1.0f,	 1.0f,	0.0f,			// v1
		 1.0f,	 1.0f,	0.0f,			// v2
		 1.0f,	 1.0f,	0.0f			// v3
	};

	static constexpr VertexNormalData	VERTEX_DATA_NRM[VERTEX_COUNT * SHAPE_VERTEX_NORMAL_DATA_ELEMENT_LEN]
	{
		//	x,		y,		z
		 0.0f,	 1.0f,	0.0f,			// n0
		 0.0f,	 1.0f,	0.0f,			// n1
		 0.0f,	 1.0f,	0.0f,			// n2
		 0.0f,	 1.0f,	0.0f			// n3
	};

	static constexpr VertexIndexData	VERTEX_DATA_IDX[INDEX_COUNT]
	{
		0, 1, 2,						// t1
		2, 1, 3							// t2
	};

public:

	static constexpr Type				SHAPE_TYPE{ QUAD };

	QuadShape()
	{}

	virtual ~QuadShape()
	{}

	virtual inline ShapeID				GetShapeID() const override { return SHAPE_TYPE; }

	virtual const size_t				GetIndexCount() const override { return INDEX_COUNT; }

	virtual const size_t				GetVertexCount() const override { return VERTEX_COUNT; }

	virtual const VertexPositionData*	GetPosition() const override { return VERTEX_DATA_POS; }

	virtual const VertexIndexData*		GetIndex() const override { return VERTEX_DATA_IDX; }

	virtual const VertexNormalData*		GetNormal() const override { return VERTEX_DATA_NRM; }

	virtual const VertexUVData*			GetUV() const override { return nullptr; }

	virtual const VertexColorData*		GetColor() const override { return nullptr; }

}; // class QuadShape

#endif // __QUAD_SHAPE__
