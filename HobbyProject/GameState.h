#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "state.h"
#include "Terraingrid.h"
#include "unit.h"
#include "collision.h"

class GameState: public State
{
public:
	GameState();
	~GameState();

	void InitZero();
	void Init();

	bool Update( float aDeltaTime );

	bool Render();

	bool HandleInput();

private:
	Vector2f	myCursorPosition;
	Sprite		myCursorSprite;
	TerrainGrid	myTerrainGrid;
	Collision	myCollision;
	Unit		myTestUnit;
};
#endif//_GAME_STATE_H_
