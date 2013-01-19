#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <Windows.h>

class Mutex
{
public:
	Mutex(CRITICAL_SECTION* aCriticalSection);
	virtual ~Mutex();
private:
	CRITICAL_SECTION* myCritSec;
};

#endif