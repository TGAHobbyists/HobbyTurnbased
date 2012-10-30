#include "CU_TimerManager.h"

CU::TimerManager::TimerManager(void)
{
	myTimers.Init(10,10);
}

CU::TimerManager::~TimerManager(void)
{
	myTimers.DeleteAll();
}

void CU::TimerManager::Update()
{
	myMasterTimer.Update(mySystemTimer.GetTime());

	for (int timerIndex = 0; timerIndex < myTimers.Count(); timerIndex++)
	{
		myTimers[timerIndex]->Update(myMasterTimer.GetDeltaTime());
	}
}

CU::Timer* CU::TimerManager::CreateTimer()
{
	Timer* newTimer = new Timer();
	myTimers.Add(newTimer);
	return newTimer;
}