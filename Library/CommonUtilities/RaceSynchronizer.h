#ifndef _RACE_SYNCRONIZER_H_
#define _RACE_SYNCRONIZER_H_
#include <Windows.h>

class RaceSynchronizer
{
public:
	inline RaceSynchronizer();
	inline ~RaceSynchronizer();

	inline void WaitToUpdate();
	inline void WaitForWork();

	inline void SetIsWorking(const bool aFlag);
	inline void SetIsDone(const bool aFlag);

	inline bool GetIsWorking() const;
	inline bool GetIsDone() const;
private:
	volatile bool myIsWorking;
	volatile bool myIsDone;
};

RaceSynchronizer::RaceSynchronizer()
{
	SetIsWorking(false);
	SetIsDone(true);
}

RaceSynchronizer::~RaceSynchronizer()
{

}

void RaceSynchronizer::WaitToUpdate()
{
	while (GetIsWorking() == true || GetIsDone() == false)
	{
		Sleep(1);
	}
}

void RaceSynchronizer::WaitForWork()
{
	while (GetIsWorking() == false || GetIsDone() == true)
	{
		Sleep(1);
	}
}

void RaceSynchronizer::SetIsWorking(const bool aFlag)
{
	myIsWorking = aFlag;
}

void RaceSynchronizer::SetIsDone(const bool aFlag)
{
	myIsDone = aFlag;
}

bool RaceSynchronizer::GetIsWorking() const
{
	return myIsWorking;
}

bool RaceSynchronizer::GetIsDone() const
{
	return myIsDone;
}

#endif