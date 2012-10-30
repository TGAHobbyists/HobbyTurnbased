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
	myPlayerAvatar.Init();
	myCurrentLocation.Init();
}

bool GameState::Update()
{
	return true;
}

bool GameState::Render()
{
	myPlayerAvatar.Render();
	myCurrentLocation.Render();
	return true;
}
