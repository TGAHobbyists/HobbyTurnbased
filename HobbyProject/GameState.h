#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "state.h"
#include "avatar.h"
#include "location.h"

class GameState: public State
{
public:
	GameState();
	~GameState();

	void InitZero();
	void Init();

	bool Update();

	bool Render();

private:
	Avatar myPlayerAvatar;
	Location myCurrentLocation;
};
#endif//_GAME_STATE_H_
