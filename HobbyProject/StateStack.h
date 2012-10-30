#ifndef _STATE_STACK_H_
#define _STATE_STACK_H_

#include "cu_growingarray.h"

class State;

class StateStack
{
public:
	StateStack();
	~StateStack();

	void Init();

	void Update();
	void Render();


private:
	CU::GrowingArray<State*> myStack;

};


#endif//_STATE_STACK_H_
