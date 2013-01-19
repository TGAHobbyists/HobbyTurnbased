#include "stdafx.h"
#include "MutexManager.h"

MutexManager::MutexManager()
{
}

MutexManager::~MutexManager()
{
	std::map<std::string, CRITICAL_SECTION*>::iterator it;
	for(it = myMutexMap.begin(); it != myMutexMap.end(); ++it)
	{
		CRITICAL_SECTION* ToDel = it->second;
		DeleteCriticalSection(&(*ToDel));
		delete(ToDel);
	}
	myMutexMap.clear();
}

CRITICAL_SECTION* MutexManager::GetMutex(std::string aName)
{
	std::map<std::string, CRITICAL_SECTION*>::iterator it;
	it = myMutexMap.find(aName);
	if(it == myMutexMap.end())
	{
		CRITICAL_SECTION* NewSection = new CRITICAL_SECTION;
		InitializeCriticalSection(&(*NewSection));
		myMutexMap.insert(std::pair<std::string, CRITICAL_SECTION*>(aName, NewSection));
		return NewSection;
	}
	return it->second;
}