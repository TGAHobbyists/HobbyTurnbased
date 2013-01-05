#include "stdafx.h"
#include "App.h"

#include "Renderer.h"

#include "gamestate.h"
#include "statecontroller.h"
#include "root.h"
#include "InputWrapper.h"

App::App()
{
	myTimer = myTimerManager.CreateTimer();
}

App::~App()
{
	
}

void App::Init()
{
	myStateStack.Init();
	StateController* controller = new StateController( &myStateStack );
	controller->Init();
	Root::GetInstance()->AttachStateController( controller );

	controller->NewGame();
}

bool App::update()
{
	myTimerManager.Update();
	float deltaTime = myTimer->GetDeltaTime();

	Root::GetInstance()->GetInputWrapper()->SwapBuffers();

	Renderer::GetInstance()->TextRender( "DO NOT WANT", Vector2f(700, 200), ALIGN_RIGHT );

	myStateStack.Update( deltaTime );

	render();
	return true;
}

void App::render()
{
	myStateStack.Render();
	Renderer::GetInstance()->Render();
}
