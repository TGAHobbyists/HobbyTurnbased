#ifndef _STATE_CONTROLLER_H_
#define _STATE_CONTROLLER_H_

class StateStack;
class GameState;

class StateController
{
public:
	StateController();
	StateController( StateStack* aStateStack );
	~StateController();

	void Init();

	void NewGame();

private:
	StateStack* myStateStack;


	GameState* myGameState;
};


#endif//_STATE_CONTROLLER_H_

