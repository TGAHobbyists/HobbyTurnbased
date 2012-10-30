#include "profilingtimer.h"
#include "profiler.h"
#include <Windows.h>

ProfilingTimer::ProfilingTimer( std::string aDataName)
{
	myDataName = "";
	myParentTimer = "";
	if( Profiler::GetInstance() != NULL )
	{
		myProfilerLink = Profiler::GetInstance();
		myDataName = aDataName;
		myProfilerLink->AddTimer( this );
		QueryPerformanceCounter( reinterpret_cast<LARGE_INTEGER*>(&myStartTime) );
	}
}
ProfilingTimer::~ProfilingTimer()
{
	if(myDataName.length() > 0)
	{
		__int64 localEndTime = 0;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&localEndTime) );

		float localSelfTime;
		localSelfTime = static_cast<float>(localEndTime - myStartTime) / myProfilerLink->GetFrequency();
		if( myParentTimer.length() == 0)
		{
			myProfilerLink->AddData(myDataName, localSelfTime);
		}
		else
		{
			myProfilerLink->AddData(myDataName, localSelfTime, myParentTimer);
		}
		myProfilerLink->RemoveTimer();
	}
}

void ProfilingTimer::SetParentTimer( std::string aParentName )
{
	myParentTimer = aParentName;
}
std::string ProfilingTimer::GetParentTimer( )
{
	return myParentTimer;
}
std::string ProfilingTimer::GetName()
{
	return myDataName;
}


