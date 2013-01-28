#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "state.h"
#include "Terraingrid.h"
#include "unit.h"
#include "collision.h"
#include "Selection.h"

class GameState: public State
{
public:
	enum InputModes
	{
		DIGGING,
		DESIGNATING_DIGGING,
		END_OF_INPUTMODES
	};
	GameState();
	~GameState();

	void InitZero();
	void Init();

	bool Update( float aDeltaTime );

	bool Render();

	bool HandleInput();

private:
	bool myMouseDown;
	int myInputMode;
	CU::GrowingArray< std::string > myInputModes;
	Vector2f	myCursorPosition;
	Sprite		myCursorSprite;
	TerrainGrid	myTerrainGrid;
	Collision	myCollision;
	Unit		myTestUnit;
	Selection	mySelection;
};
#endif//_GAME_STATE_H_
