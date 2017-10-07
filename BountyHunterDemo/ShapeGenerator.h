///-------------------------------------------------------------------------------------------------
/// File:	ShapeGenerator.h.
///
/// Summary:	Declares the shape generator class.
///-------------------------------------------------------------------------------------------------


#ifndef __SHAPE_GENERATOR_H__
#define __SHAPE_GENERATOR_H__

#include "Shape.h"

#include <vector>

class Shape;

class ShapeGenerator
{
	using ShapeRegistry = std::vector<IShape*>;

private:	

	ShapeGenerator();

	ShapeGenerator(const ShapeGenerator&) = delete;
	ShapeGenerator& operator=(const ShapeGenerator&) = delete;

	ShapeRegistry m_ShapeRegistry;

public:

	static ShapeGenerator& GetInstance()
	{
		static ShapeGenerator INSTANCE;
		return INSTANCE;
	}

	~ShapeGenerator();

	template<class S>
	static Shape CreateShape()
	{		
		ShapeGenerator& instance = ShapeGenerator::GetInstance();

		IShape* shape = nullptr;

		shape = instance.m_ShapeRegistry[S::SHAPE_TYPE];

		// return a new shape of this type
		if (shape != nullptr)
			return Shape(shape);


		// shape tyep not instantiated yet
		shape = new S;
		instance.m_ShapeRegistry[S::SHAPE_TYPE] = shape;

		return Shape(shape);
	}

}; // class ShapeGenerator

#endif // __SHAPE_GENERATOR_H__
