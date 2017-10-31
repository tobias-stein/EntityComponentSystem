///-------------------------------------------------------------------------------------------------
/// File:	Wall.h.
///
/// Summary:	Declares the wall class.
///-------------------------------------------------------------------------------------------------

#ifndef __WALL_ENTITY_H__
#define __WALL_ENTITY_H__

#include "GameObject.h"
#include "GameTypes.h"

class Wall : public GameObject<Wall>
{
public:

	Wall(const glm::vec3& size);
	virtual ~Wall();

}; // class Wall

#endif // __WALL_ENTITY_H__
