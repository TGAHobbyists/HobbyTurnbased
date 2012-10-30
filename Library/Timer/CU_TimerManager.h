#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_
#include "CU_SystemTimer.h"
#include "CU_Timer.h"

namespace CommonUtilities
{
	class TimerManager
	{
	public:
		TimerManager(void);
		~TimerManager(void);
		void Update();
		Timer* CreateTimer();
	private:
		SystemTimer		mySystemTimer;
		Timer			myMasterTimer;
		CU::GrowingArray<Timer*> myTimers;
	};
}

namespace CU = CommonUtilities;

#endif