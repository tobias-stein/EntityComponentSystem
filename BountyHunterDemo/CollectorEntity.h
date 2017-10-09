///-------------------------------------------------------------------------------------------------
/// File:	CollectorEntity.h
///
/// Summary:	Declares the collector class. A collector is a player character which goal is to
/// collect bounty.
///-------------------------------------------------------------------------------------------------

#ifndef __COLLECTOR_ENTITY_H__
#define __COLLECTOR_ENTITY_H__

#include "GameObject.h"

class CollectorEntity : public GameObject<CollectorEntity>
{
private:

public:

	CollectorEntity(bool humanPlayer);
	~CollectorEntity();

}; // class CollectorEntity

#endif // __COLLECTOR_ENTITY_H__
