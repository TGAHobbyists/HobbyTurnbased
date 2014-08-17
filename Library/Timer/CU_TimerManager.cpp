#include "CU_TimerManager.h"

CU::TimerManager::TimerManager(void)
{
	m_pTimers.Init(10,10);
}

CU::TimerManager::~TimerManager(void)
{
	m_pTimers.DeleteAll();
}

void CU::TimerManager::Update()
{
	myMasterTimer.Update(mySystemTimer.GetTime());

	for (int timerIndex = 0; timerIndex < m_pTimers.Count(); timerIndex++)
	{
		m_pTimers[timerIndex]->Update(myMasterTimer.GetDeltaTime());
	}
}

CU::Timer* CU::TimerManager::CreateTimer()
{
	Timer* newTimer = new Timer();
	m_pTimers.Add(newTimer);
	return newTimer;
}