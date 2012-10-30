#include "stdafx.h"
#include "App.h"

#include "Renderer.h"

#include "gamestate.h"
#include "statecontroller.h"
#include "root.h"

App::App()
{


	myTimer = myTimerManager.CreateTimer();

}

App::~App()
{
	
}

void App::Init()
{
	StateController* controller = new StateController( &myStateStack );
	controller->Init();
	Root::GetInstance()->AttachStateController( controller );

	controller->NewGame();
}

bool App::update()
{

	Renderer::GetInstance()->TextRender( "DO NOT WANT", Vector2f(700, 200), ALIGN_RIGHT );

	myStateStack.Update();

	render();
	return true;
}

void App::render()
{
	myStateStack.Render();
	Renderer::GetInstance()->Render();
}
