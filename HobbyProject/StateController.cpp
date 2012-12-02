#include "stdafx.h"
#include "stateController.h"

#include "gameState.h"
#include "stateSTack.h"

StateController::StateController()
{

}
StateController::StateController( StateStack* aStateStack )
:myStateStack( aStateStack )
{}
StateController::~StateController()
{

}

void StateController::Init()
{
	myGameState = new GameState();
	myGameState->InitZero();
}

void StateController::NewGame()
{
	myGameState->Init();
	myStateStack->Push( myGameState );
}
