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
}

bool GameState::Update()
{
	return true;
}

bool GameState::Render()
{
	myTerrainGrid.Render();

	return true;
}
