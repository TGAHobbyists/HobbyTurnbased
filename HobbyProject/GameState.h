#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "state.h"
#include "Terraingrid.h"
#include "avatar.h"
#include "collision.h"
#include "Enemy.h"
#include "ActorContainer.h"

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
	void OnMouseDown();
	CU::GrowingArray< Enemy* > myTestDYNAMICALLOCenemyArray;
	bool myMouseDown;
	CU::GrowingArray< std::string > myInputModes;
	Vector2f	myCursorPosition;
	Sprite		myCursorSprite;
	TerrainGrid	myTerrainGrid;
	Collision*	myCollision;
	Avatar		myTestUnit;
	ActorContainer myActorContainer;
};
#endif//_GAME_STATE_H_
