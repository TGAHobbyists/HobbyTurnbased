#ifndef _TIMER_H_
#define _TIMER_H_
#include "CU_GrowingArray.h"

namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer(void);
		~Timer(void);
		void Update(const float someTime);
		Timer* CreateChildTimer();
		
		inline void SetPaused(const bool aFlag)
		{
			myIsPaused = aFlag;
		}

		inline bool IsPaused() const
		{
			return myIsPaused;
		}

		inline float GetElapsedTime() const
		{
			return myElapsedTime;
		}

		inline float GetDeltaTime() const
		{
			return myLastDeltaTime;
		}

		inline void Reset()
		{
			myElapsedTime = 0.0f;
			myLastDeltaTime = 0.0f;
		}

	private:
		Timer(const Timer &aTimer);
	private:
		CU::GrowingArray<Timer*> myChildren;
		float myElapsedTime;
		float myLastDeltaTime;
		bool myIsPaused;
	};
}

namespace CU = CommonUtilities;

#endif