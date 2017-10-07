///-------------------------------------------------------------------------------------------------
/// File:	ShapeBufferIndex.h.
///
/// Summary:	Declares the shape buffer index class. This class provides a set of indices used
/// for rendering a shape.
///-------------------------------------------------------------------------------------------------

#ifndef __SHAPE_BUFFER_INDEX_H__
#define __SHAPE_BUFFER_INDEX_H__

class ShapeBufferIndex
{
	friend class RenderSystem;

protected:

	size_t	m_PositionDataIndex;

	size_t	m_IndexDataIndex;

	size_t	m_NormalDataIndex;

	size_t	m_TexCoordDataIndex;

	size_t	m_ColorDataIndex;

public:

	ShapeBufferIndex() :
		m_PositionDataIndex(-1),
		m_IndexDataIndex(-1),
		m_NormalDataIndex(-1),
		m_TexCoordDataIndex(-1),
		m_ColorDataIndex(-1)
	{}

	inline size_t GetPositionDataIndex() const { return this->m_PositionDataIndex; }

	inline size_t GetIndexDataIndex() const { return this->m_IndexDataIndex; }

	inline size_t GetNormalDataIndex() const { return this->m_NormalDataIndex; }

	inline size_t GetTexCoordDataIndex() const { return this->m_TexCoordDataIndex; }

	inline size_t GetColorDataIndex() const { return this->m_ColorDataIndex; }

}; // class ShapeBufferIndex

#endif // __SHAPE_BUFFER_INDEX_H__
