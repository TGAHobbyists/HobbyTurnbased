#include "stdafx.h"
#include "avatar.h"

#include "renderer.h"

Avatar::Avatar()
:myHealth(-1)
{

}
Avatar::~Avatar()
{

}

void Avatar::Init()
{
	myHealth = 100;
}

void Avatar::Render()
{
	Renderer::GetInstance()->TextRender( "HP: %i", Vector2f(100, 200), ALIGN_LEFT );
}