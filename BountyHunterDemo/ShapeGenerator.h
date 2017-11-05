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

	static ShapeGenerator& GetInstance()
	{
		static ShapeGenerator INSTANCE;
		return INSTANCE;
	}

public:

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


		// shape type not instantiated yet
		shape = new S;

		bool isInitialized = shape->Initialize();
		assert((isInitialized == true) && "Failed to initialize shape!");
		fprintf(stdout, "Shape #%d initialized.\n", S::SHAPE_TYPE);

		instance.m_ShapeRegistry[S::SHAPE_TYPE] = shape;

		return Shape(shape);
	}

}; // class ShapeGenerator

#endif // __SHAPE_GENERATOR_H__
