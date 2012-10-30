#ifndef _PAUSE_SYNCRONIZER_H_
#define _PAUSE_SYNCRONIZER_H_
#include <Windows.h>

class PauseSynchronizer
{
public:
	inline PauseSynchronizer();
	inline ~PauseSynchronizer();

	inline void PauseThread();
	inline void ResumeThread();
	inline void TryToWork();
	inline void EndWork();

private:
	volatile bool myIsWorking;
	volatile bool myShouldPause;
};

PauseSynchronizer::PauseSynchronizer()
{
	myIsWorking = false;
	myShouldPause = false;
}

PauseSynchronizer::~PauseSynchronizer()
{

}

void PauseSynchronizer::PauseThread()
{
	myShouldPause = true;
	while(myIsWorking == true)
	{
		Sleep(1);
	}
}

void PauseSynchronizer::ResumeThread()
{
	myShouldPause = false;
}

void PauseSynchronizer::TryToWork()
{
	do 
	{
		Sleep(1);
	} 
	while (myShouldPause == true);

	myIsWorking = true;
}

void PauseSynchronizer::EndWork()
{
	myIsWorking = false;
}

#endif