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

	static constexpr float				VERTEX_DATA_POS[VERTEX_COUNT * 3]
	{};

	static constexpr float				VERTEX_DATA_NRM[VERTEX_COUNT * 3]
	{};

	static constexpr unsigned short		VERTEX_DATA_IDX[VERTEX_COUNT]
	{};

public:

	static constexpr Type				SHAPE_TYPE{ QUAD };

	QuadShape()
	{}
	virtual ~QuadShape()
	{}

	virtual const size_t				GetVertexCount() const override { return VERTEX_COUNT; }

	virtual const float*				GetPosition() const override { return VERTEX_DATA_POS; }

	virtual const unsigned short*		GetIndex() const override { return VERTEX_DATA_IDX; }

	virtual const float*				GetNormal() const override { return VERTEX_DATA_NRM; }

	virtual const float*				GetUV() const override { return nullptr; }

	virtual const float*				GetColor() const override { return nullptr; }

}; // class QuadShape

#endif // __QUAD_SHAPE__
