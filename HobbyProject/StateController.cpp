#include "stdafx.h"
#include "stateController.h"

#include "gameState.h"

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
	myGameState->InitZero();
}

void StateController::NewGame()
{
	
}
