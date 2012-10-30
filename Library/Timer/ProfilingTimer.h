#ifndef _PROFILING_TIMER_H_
#define _PROFILING_TIMER_H_

#include "profilingData.h"
#include <string>
class Profiler;

class ProfilingTimer
{
public:
	ProfilingTimer( std::string aDataName);
	~ProfilingTimer();
	void SetParentTimer( std::string aParentName );
	std::string GetParentTimer( );
	std::string GetName();


private:
	__int64 myStartTime;
	Profiler* myProfilerLink;
	std::string myDataName;
	std::string myParentTimer;

};



#endif//_PROFILING_TIMER_H_
