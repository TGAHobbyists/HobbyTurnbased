#include "stdafx.h"
#include "App.h"

#include "Renderer.h"

#include "gamestate.h"
#include "statecontroller.h"
#include "root.h"
#include "InputWrapper.h"

App::App()
{
	m_pTimer = m_TimerManager.CreateTimer();
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
	m_TimerManager.Update();
	float deltaTime = m_pTimer->GetDeltaTime();

	Root::GetInstance()->GetInputWrapper()->SwapBuffers();

	myStateStack.Update( deltaTime );

	render();
	return true;
}

void App::render()
{
	myStateStack.Render();
	Renderer::GetInstance()->Render();
}

