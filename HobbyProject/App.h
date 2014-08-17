#ifndef _APP_H_
#define _APP_H_

#include "CU_TimerManager.h"


#include "statestack.h"

#include "Vector.h"


class App
{
public:
	App();
	~App();
	void Init();
	bool update();

	void render();

private:
	CU::TimerManager m_TimerManager;
	CU::Timer* m_pTimer;

	StateStack myStateStack;
};

#endif //!_APP_H_