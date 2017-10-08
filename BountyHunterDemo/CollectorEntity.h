///-------------------------------------------------------------------------------------------------
/// File:	CollectorEntity.h
///
/// Summary:	Declares the collector class. A collector is a player character which goal is to
/// collect bounty.
///-------------------------------------------------------------------------------------------------

#ifndef __COLLECTOR_ENTITY_H__
#define __COLLECTOR_ENTITY_H__

#include <ECS.h>

class CollectorEntity : public ECS::Entity<CollectorEntity>
{
private:

public:

	CollectorEntity(bool humanPlayer);
	~CollectorEntity();

}; // class CollectorEntity

#endif // __COLLECTOR_ENTITY_H__
