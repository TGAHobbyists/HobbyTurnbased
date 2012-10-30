#ifndef _PROFILING_NODE_H_
#define _PROFILING_NODE_H_

#include "profilingData.h"
#include "cu_timer.h"

class ProfilingNode
{
public:
	ProfilingNode();
	~ProfilingNode();

	void AddData( ProfilingData someData );


private:
	ProfilingData myData;

};



#endif//_PROFILING_NODE_H_
