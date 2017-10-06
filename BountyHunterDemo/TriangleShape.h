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

	static constexpr float				VERTEX_DATA_POS[VERTEX_COUNT * 3]
	{};

	static constexpr float				VERTEX_DATA_NRM[VERTEX_COUNT * 3]
	{};

	static constexpr unsigned short		VERTEX_DATA_IDX[VERTEX_COUNT]
	{};

public:

	static constexpr Type				SHAPE_TYPE { TRIANLGE };

	TriangleShape()
	{}

	virtual ~TriangleShape()
	{}

	virtual const size_t				GetVertexCount() const override { return VERTEX_COUNT; }

	virtual const float*				GetPosition() const override { return VERTEX_DATA_POS; }

	virtual const unsigned short*		GetIndex() const override { return VERTEX_DATA_IDX; }

	virtual const float*				GetNormal() const override { return VERTEX_DATA_NRM; }

	virtual const float*				GetUV() const override { return nullptr; }

	virtual const float*				GetColor() const override { return nullptr; }

}; // class TriangleShape

#endif // __TRIANGLE_SHAPE__
