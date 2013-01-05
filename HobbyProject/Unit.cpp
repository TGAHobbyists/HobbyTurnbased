#include "stdafx.h"
#include "unit.h"

#include "renderer.h"
#include "collision.h"

Unit::Unit()
{
}
Unit::~Unit()
{}

void Unit::Init()
{
	myMovement.myY = 19.42f;
	myPosition = Vector2f( 20,0);
	Vector2f unitSize = Vector2f(16,32);
	mySprite.SetTexture( Renderer::GetInstance()->CreateTexture( "Sprites//Unit//Unit.png" ), unitSize );
	myOffset = Vector2f( mySprite.GetRawSprite()->GetWidth()/2, mySprite.GetRawSprite()->GetHeight() );
}

void Unit::Update( float aDeltaTime, Collision* aCollisionChecker )
{
	myMovement.myY += (9.82f) * 40 * aDeltaTime;
	Vector2f change = Vector2f( 0, myMovement.myY * aDeltaTime );
	Vector2f actualPosition = myPosition;
	if( !aCollisionChecker->IsValidMove( myPosition, change ) )
	{
		myMovement.myY = 0;
	}
	change = myMovement * aDeltaTime;
	if( aCollisionChecker->IsValidMove( myPosition, change ) )
	{
		myPosition += change;
		mySprite.SetPosition( myPosition - myOffset );
	}
}
void Unit::Render()
{
	Renderer::GetInstance()->SpriteRender( &mySprite );
}
void Unit::StartMoveRight()
{
	myMovement.myX += 80.f;
}
void Unit::StopMoveRight()
{
	myMovement.myX -= 80.f;
}
void Unit::StartMoveLeft()
{
	myMovement.myX -= 80.f;
}
void Unit::StopMoveLeft()
{
	myMovement.myX += 80.f;
}
void Unit::Jump()
{
	if( !IsInAir() )
		myMovement.myY = -200.f;
}
bool Unit::IsInAir() const
{
	return myMovement.myY != 0;
}
