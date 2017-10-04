///-------------------------------------------------------------------------------------------------
/// File:	Collector.h.
///
/// Summary:	Declares the collector class. A collector is a player character which goal is to
/// collect bounty.
///-------------------------------------------------------------------------------------------------

#ifndef __COLLECTOR_H__
#define __COLLECTOR_H__

#include <ECS.h>

class Collector : public ECS::Entity<Collector>
{
private:

public:

	Collector(bool humanPlayer);
	~Collector();

}; // class Collector

#endif // __COLLECTOR_H__
