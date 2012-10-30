#include "CU_Timer.h"

CU::Timer::Timer(void)
{
	myIsPaused = false;
	myElapsedTime = 0.0f;
	myLastDeltaTime = 0.0f;
	myChildren.Init(1,1);
}

CU::Timer::Timer(const Timer &aTimer)
{
	myChildren		= aTimer.myChildren;
	myElapsedTime	= aTimer.myElapsedTime;
	myLastDeltaTime	= aTimer.myLastDeltaTime;
	myIsPaused		= aTimer.myIsPaused;
}

CU::Timer::~Timer(void)
{
	myChildren.DeleteAll();
}

void CU::Timer::Update(const float someTime)
{
	if (IsPaused() == false)
	{
		myElapsedTime += someTime;

		for (int timerIndex = 0; timerIndex < myChildren.Count(); timerIndex++)
		{
			myChildren[timerIndex]->Update(someTime);
		}

		myLastDeltaTime = someTime;
	}
}

CU::Timer* CU::Timer::CreateChildTimer()
{
	Timer* newTimer = new Timer();
	myChildren.Add(newTimer);
	return newTimer;
}