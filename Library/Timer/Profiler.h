#ifndef _PROFILER_H_
#define _PROFILER_H_

#include "CU_HashTable.h"
#include "cu_stack.h"
#include "profilingtimer.h"

class Profiler
{
public:
	Profiler();
	~Profiler();
	static void Create();
	static void Destroy();
	static Profiler* GetInstance();

	__int64 GetFrequency() const;
	void AddData( std::string aDataName, float aSelfTime, std::string aParentTimer  = "" );
	void AddTimer( ProfilingTimer* aTimer );
	void RemoveTimer();
	//void TemporaryDraw(hgeFont* aFont);
	void NewFrame();



private:
	static Profiler* ourInstance;

	CU::StaticArray< CU::HashTable< ProfilingData >, 3 > myData;
	CU::Stack< ProfilingTimer* > m_pTimerStack;
	CU::GrowingArray< std::string > m_pTimerNames;

	int myCurrentFrame;

	__int64 myFrequency;
	__int64 myStartTime;

};



#endif//_PROFILER_H_
