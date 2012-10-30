#include "CU_SystemTimer.h"

CU::SystemTimer::SystemTimer(void)
{
	myPreviousTime = 0;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&myPreviousTime));

	myFrequency = 0;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&myFrequency));
}

CU::SystemTimer::SystemTimer(const SystemTimer &aSystemTimer)
{
	myFrequency		= aSystemTimer.myFrequency;
	myPreviousTime	= aSystemTimer.myPreviousTime;
}

CU::SystemTimer::~SystemTimer(void)
{

}

float CU::SystemTimer::GetTime()
{
	__int64 currentTime = 0;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));
	
	float deltaTime = static_cast<float>(currentTime-myPreviousTime) / myFrequency;
	myPreviousTime = currentTime;
	
	return(deltaTime);
}