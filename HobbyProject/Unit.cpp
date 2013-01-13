#include "stdafx.h"
#include "unit.h"

#include "renderer.h"
#include "collision.h"

#include "tile.h"

Unit::Unit()
{
}
Unit::~Unit()
{}

void Unit::Init()
{
	myMovement.myY = 19.42f;
	myCollisionObject.myPosition = Vector2f( 25,5);
	Vector2f unitSize = Vector2f(16,32);
	mySprite.SetTexture( Renderer::GetInstance()->CreateTexture( "Sprites//Unit//Unit.png" ), unitSize );
	//myOffset = Vector2f( mySprite.GetRawSprite()->GetWidth()/2, mySprite.GetRawSprite()->GetHeight() );,
	myCollisionObject.myMinOffset = Vector2f( mySprite.GetRawSprite()->GetWidth() * -0.5f, mySprite.GetRawSprite()->GetHeight() * -1.f );
	myCollisionObject.myMaxOffset = Vector2f( mySprite.GetRawSprite()->GetWidth() * 0.5f, 0 );
}

void Unit::Update( float aDeltaTime, Collision* aCollisionChecker )
{
	myMovement.myY += (9.82f) * 40 * aDeltaTime;
	Vector2f change = Vector2f( 0, myMovement.myY * aDeltaTime );
	if( !aCollisionChecker->IsValidMoveFat( myCollisionObject.myPosition, change, 7.f ) )
	{
		myMovement.myY = 0;
	}
	change = myMovement * aDeltaTime;
	if( !aCollisionChecker->IsValidMoveFat( myCollisionObject.myPosition, change, 7.f ) )
	{
		change.myX = 0;
	}
	myCollisionObject.myPosition += change;
	mySprite.SetPosition( myCollisionObject.GetMinPosition() );
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
void Unit::DEBUGDigDown( Collision* aCollision )
{
	Vector2f direction( 0, 15 );
	aCollision->GetTileInDirection( myCollisionObject.myPosition, direction ).Strike( 1 );
}
