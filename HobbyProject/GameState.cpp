#include "stdafx.h"
#include "gamestate.h"
#include "InputWrapper.h"
#include "renderer.h"
#include "avatar.h"

GameState::GameState()
{

}
GameState::~GameState()
{
	Collision::Destroy();
	myCollision = NULL;
}

void GameState::InitZero()
{

}

void GameState::Init()
{
	myMouseDown = false;
	myTerrainGrid.Init();
	myTestUnit.Init();
	Collision::Create();
	myCollision = Collision::GetInstance();
	myCollision->Init( &myTerrainGrid );
	Vector2f cursorSize( 32,32 );
	myCursorSprite = Renderer::GetInstance()->CreateTexture( "Sprites//Fab cursor.png" );
	mySelection.Init();
}

bool GameState::Update( float aDeltaTime )
{
	myTestUnit.Update( aDeltaTime, myCollision );
	HandleInput();
	mySelection.Update( aDeltaTime );
	return true;
}

bool GameState::Render()
{
	myTerrainGrid.Render();
	myTestUnit.Render();
	myCursorSprite.SetPosition( myCursorPosition );
	mySelection.Render();
	Renderer::GetInstance()->SpriteRender( &myCursorSprite );
	myCollision->RenderDebug();

	return true;
}
bool GameState::HandleInput()
{
	Input::InputWrapper* input = Root::GetInstance()->GetInputWrapper();
	const CU::GrowingArray<Input::InputEvent>& events = input->GetInputBuffer();

	static Vector2f lastMouseMovement;
	myCursorPosition += input->GetMouseMovement() - lastMouseMovement;
	lastMouseMovement = input->GetMouseMovement();
	myCursorPosition.myX = CLAMP(0.f, myCursorPosition.myX, Root::GetInstance()->myResolutionWidth - 1.f);
	myCursorPosition.myY = CLAMP(0.f, myCursorPosition.myY, Root::GetInstance()->myResolutionHeight -1.f);
	for( int index = 0; index < events.Count(); ++index )
	{
		if( events[index].myInputType == Input::Mouse )
		{
			if( events[index].myMouseButton == Input::LeftMouseButton )
			{
				if( events[index].myInputAction == Input::Press )
				{
					myMouseDown = true;
				}
				if( events[index].myInputAction == Input::Release )
				{
					myMouseDown = false;
				}
			}
		}
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
			if( events[index].myKey == DIK_D )
			{
				if( events[index].myInputAction == Input::Press )
				{
					myTestUnit.Attack();
				}
			}
		}
	}
	return true;
}
