#ifndef _PROFILING_DATA_H_
#define _PROFILING_DATA_H_

#include <string>

struct ProfilingData
{
	ProfilingData()
	{
		mySelfTime = 0;
		myTotalTime = 0;
		myTimesCalled = -1;
		parentNode = "";
	}
	bool operator==( ProfilingData aRightHandObject )
	{
		if( mySelfTime != aRightHandObject.mySelfTime )
		{
			return false;
		}
		if( myTimesCalled != aRightHandObject.myTimesCalled )
		{
			return false;
		}
		return true;
	}
	float mySelfTime;
	float myTotalTime;
	int myTimesCalled;
	std::string parentNode;
};

#endif//_PROFILING_DATA_H_
