///-------------------------------------------------------------------------------------------------
/// File:	GameObject.h.
///
/// Summary:	Declares the base game object entity class. Any object placed "physically", that is,
/// with 2D/3D coordinates in the virtual world must derive from this class.
///-------------------------------------------------------------------------------------------------


#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <ECS/ECS.h>

template<class T>
class GameObject : public ECS::Entity<T>
{
public:

	GameObject()
	{}

	virtual ~GameObject()
	{}
};

#endif // __GAME_OBJECT_H__
