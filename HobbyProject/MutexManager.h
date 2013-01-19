#ifndef _MUTEX_MANAGER_H_
#define _MUTEX_MANAGER_H_

#include <Windows.h>
#include <map>
#include <string>
#include "Mutex.h"
#include "root.h"

class MutexManager
{
public:
	MutexManager();
	virtual ~MutexManager();
	CRITICAL_SECTION* GetMutex(std::string aName);
private:
	std::map<std::string, CRITICAL_SECTION*> myMutexMap;
};

#endif