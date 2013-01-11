#include "stdafx.h"
#include "gamestate.h"
#include "InputWrapper.h"

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
	HandleInput();
	return true;
}

bool GameState::Render()
{
	myTerrainGrid.Render();
	myTestUnit.Render();

	return true;
}
bool GameState::HandleInput()
{
	Input::InputWrapper* input = Root::GetInstance()->GetInputWrapper();
	const CU::GrowingArray<Input::InputEvent>& events = input->GetInputBuffer();

	for( int index = 0; index < events.Count(); ++index )
	{
		if( events[index].myInputType == Input::Keyboard )
		{
			if( events[index].myKey == DIK_LEFT )
			{
				if( events[index].myInputAction == Input::Press )
				{
					myTestUnit.StartMoveLeft();
				}
				if( events[index].myInputAction == Input::Release )
				{
					myTestUnit.StopMoveLeft();
				}
			}
			if( events[index].myKey == DIK_RIGHT )
			{
				if( events[index].myInputAction == Input::Press )
				{
					myTestUnit.StartMoveRight();
				}
				if( events[index].myInputAction == Input::Release )
				{
					myTestUnit.StopMoveRight();
				}
			}
			if( events[index].myKey == DIK_SPACE )
			{
				if( events[index].myInputAction == Input::Press )
				{
					myTestUnit.Jump();
				}
			}
			if( events[index].myKey == DIK_DOWN )
			{
				if( events[index].myInputAction == Input::Press )
				{
					myTestUnit.DEBUGDigDown( &myCollision );
				}
			}
		}
	}
	return true;
}
