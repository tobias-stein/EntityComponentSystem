///-------------------------------------------------------------------------------------------------
/// File:	IShape.h.
///
/// Summary:	Declares the IShape interface.
///-------------------------------------------------------------------------------------------------

#ifndef __I_SHAPE_H__
#define __I_SHAPE_H__

#include <stdint.h>

#include "OpenGL.h"




typedef uint16_t ShapeID;

static constexpr ShapeID INVALID_SHAPE_ID { 0xffff };

///-------------------------------------------------------------------------------------------------
/// Class:	IShape
///
/// Summary:	Base shape interface each specific shape must implement.
///
/// Author:	Tobias Stein
///
/// Date:	6/10/2017
///-------------------------------------------------------------------------------------------------

class IShape
{
public:

	enum Type
	{
		INVALID_SHAPE	= INVALID_SHAPE_ID,
		TRIANLGE		= 0,
		QUAD			= 1,

		MAX_SHAPES
	}; // enum Type


	IShape();

	virtual ~IShape();

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual inline unsigned long IShape::GetShapeID() const
	///
	/// Summary:	Gets shape unique identifier.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	7/10/2017
	///
	/// Returns:	The shape identifier.
	///-------------------------------------------------------------------------------------------------

	virtual inline ShapeID GetShapeID() const { return INVALID_SHAPE; }

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual bool IShape::Initialize();
	///
	/// Summary:	Initializes the shape.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	6/10/2017
	///
	/// Returns:	True if it succeeds, false if it fails.
	///-------------------------------------------------------------------------------------------------

	virtual bool Initialize() { return true; }

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual void IShape::Release();
	///
	/// Summary:	Releases this shape object's aqcuired resources.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	6/10/2017
	///-------------------------------------------------------------------------------------------------

	virtual void Release() {}

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual const size_t IShape::GetVertexCount() const = 0;
	///
	/// Summary:	Gets number of vertices.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	6/10/2017
	///
	/// Returns:	The vertex number.
	///-------------------------------------------------------------------------------------------------

	virtual const size_t GetVertexCount() const = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual const size_t IShape::GetTriangleCount() const = 0;
	///
	/// Summary:	Gets triangle count.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	7/10/2017
	///
	/// Returns:	The triangle count.
	///-------------------------------------------------------------------------------------------------

	virtual const size_t GetTriangleCount() const = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual const size_t IShape::GetIndexCount() const = 0;
	///
	/// Summary:	Returns the number of indices used for this shape. 
	///
	/// Author:	Tobias Stein
	///
	/// Date:	7/10/2017
	///
	/// Returns:	The index count or 0 if no indices are used
	///-------------------------------------------------------------------------------------------------

	virtual const size_t GetIndexCount() const = 0;

	// >>> SHAPE ATTRIBUTES >>>
	 
	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual const float* IShape::GetPosition() const = 0;
	///
	/// Summary:	Get a raw float array of vertex position values (x,y,y).
	///
	/// Author:	Tobias Stein
	///
	/// Date:	6/10/2017
	///
	/// Returns:	Null if it fails, else the position array.
	///-------------------------------------------------------------------------------------------------

	virtual const VertexPositionData* GetPosition() const = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual const unsigned short IShape::GetIndex() const = 0;
	///
	/// Summary:	Gets the index.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	6/10/2017
	///
	/// Returns:	The index data, null if no index data is provided.
	///-------------------------------------------------------------------------------------------------

	virtual const VertexIndexData* GetIndex() const = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual const float* IShape::GetNormal() const = 0;
	///
	/// Summary:	Gets the normal values for the vertices.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	6/10/2017
	///
	/// Returns:	Null if shape does not has normal's, else the normal array.
	///-------------------------------------------------------------------------------------------------

	virtual const VertexNormalData* GetNormal() const = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual const float* IShape::GetTexCoord() const = 0;
	///
	/// Summary:	Gets the uv texture coordinates for each vertex.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	6/10/2017
	///
	/// Returns:	Null if shape does not has uv's, else the uv array.
	///-------------------------------------------------------------------------------------------------

	virtual const VertexTexCoordData* GetTexCoord() const = 0;

	///-------------------------------------------------------------------------------------------------
	/// Fn:	virtual const float* IShape::GetColor() const = 0;
	///
	/// Summary:	Gets the color vertex attribute.
	///
	/// Author:	Tobias Stein
	///
	/// Date:	6/10/2017
	///
	/// Returns:	Null if no color data is provided, else the color data array.
	///-------------------------------------------------------------------------------------------------

	virtual const VertexColorData* GetColor() const = 0;

}; // class IShape

#endif // __I_SHAPE_H__