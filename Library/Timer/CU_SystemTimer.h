#ifndef _SYSTEM_TIMER_H_
#define _SYSTEM_TIMER_H_
#include <Windows.h>

namespace CommonUtilities
{
	class SystemTimer
	{
	public:
		SystemTimer(void);
		~SystemTimer(void);
		float GetTime();
	private:
		SystemTimer(const SystemTimer &aSystemTimer);
	private:
		__int64 myPreviousTime;
		__int64 myFrequency;
	};
}

namespace CU = CommonUtilities;

#endif