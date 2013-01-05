#include "stdafx.h"
#include "gamestate.h"

GameState::GameState()
{

}
GameState::~GameState()
{

}

void GameState::InitZero()
{

}

void GameState::Init()
{
	myTerrainGrid.Init();
	myTestUnit.Init();
	myCollision.Init( &myTerrainGrid );
}

bool GameState::Update( float aDeltaTime )
{
	myTestUnit.Update( aDeltaTime, &myCollision );
	return true;
}

bool GameState::Render()
{
	myTerrainGrid.Render();
	myTestUnit.Render();

	return true;
}
