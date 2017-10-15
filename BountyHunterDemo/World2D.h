///-------------------------------------------------------------------------------------------------
/// File:	World2D.h.
///
/// Summary:	Declares the world 2D.
///-------------------------------------------------------------------------------------------------

#ifndef __WORLD_2D_H__
#define __WORLD_2D_H__

#include "IWorld.h"


///-------------------------------------------------------------------------------------------------
/// Class:	World2D
///
/// Summary:	A 2D world. This world only cares about x and y coordinates.
///
/// Author:	Tobias Stein
///
/// Date:	12/10/2017
///-------------------------------------------------------------------------------------------------

class World2D : public IWorld
{
public:

	World2D(const Bounds2D& worldBounds, const glm::vec2& worldUp = glm::vec2(0.0f, 1.0f));
	virtual ~World2D();

}; // class World2D

#endif // __WORLD_2D_H__
