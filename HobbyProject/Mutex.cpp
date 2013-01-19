#include "stdafx.h"
#include "Mutex.h"

Mutex::Mutex(CRITICAL_SECTION* aCriticalSection)
{
	myCritSec = aCriticalSection;
	EnterCriticalSection(&(*myCritSec));
}

Mutex::~Mutex()
{
	LeaveCriticalSection(&(*myCritSec));
}

