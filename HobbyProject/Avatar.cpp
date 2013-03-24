#include "stdafx.h"
#include "avatar.h"

#include "renderer.h"
#include "collision.h"

#include "tile.h"

Avatar::Avatar()
{
}
Avatar::~Avatar()
{}

void Avatar::Init()
{
	myMovement.myY = 19.42f;
	myCollisionObject.myPosition = Vector2f( 25,5);
	mySprite = Renderer::GetInstance()->CreateTexture( "Sprites//Unit//Unit.png" );
	myCollisionObject.myMinOffset = Vector2f( mySprite.GetSize().x * -0.5f, mySprite.GetSize().y * -1.f );
	myCollisionObject.myMaxOffset = Vector2f( mySprite.GetSize().x * 0.5f, 0 );

	Vector2f debufsize(32,32);
	debugsprite = Renderer::GetInstance()->CreateTexture( "Sprites//Fab cursor.png" );
	myAttackComponent.Init();
	myAttackComponent.AddAttack();
}

void Avatar::Update( float aDeltaTime, Collision* aCollisionChecker )
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
	if( change.myX > 0 )
		myLastMovementDirection = 1.0f;
	else if( change.myX < 0 )
		myLastMovementDirection = -1.f;
	myCollisionObject.myPosition += change;
	mySprite.SetPosition( myCollisionObject.GetMinPosition() );
	myAttackComponent.Update( aDeltaTime, myCollisionObject.myPosition, myLastMovementDirection );
}
void Avatar::Render()
{
	Renderer::GetInstance()->SpriteRender( &mySprite );
	myAttackComponent.DEBUGRender();
	//Renderer::GetInstance()->SpriteRender( &debugsprite );
}
void Avatar::StartMoveRight()
{
	myMovement.myX += 80.f;
}
void Avatar::StopMoveRight()
{
	myMovement.myX -= 80.f;
}
void Avatar::StartMoveLeft()
{
	myMovement.myX -= 80.f;
}
void Avatar::StopMoveLeft()
{
	myMovement.myX += 80.f;
}
void Avatar::Jump()
{
	if( !IsInAir() )
		myMovement.myY = -200.f;
}
bool Avatar::IsInAir() const
{
	return myMovement.myY != 0;
}
void Avatar::DEBUGDigDown( Collision* aCollision )
{
	Vector2f direction( 0, 15 );
	aCollision->GetTileInDirection( myCollisionObject.myPosition, direction ).Strike( 1 );
}
void Avatar::DigInDirection( Vector2f aDirection, Collision* aCollision )
{
	Vector2f direction = aDirection.Normalize() * 23.f;
	aCollision->GetTileInDirection( myCollisionObject.GetMiddlePosition(), direction ).Strike( 1 );
	//debugsprite.SetPosition( myCollisionObject.GetMiddlePosition() + aDirection.Normalize() * 23.f );
}

void Avatar::Attack()
{
	myAttackComponent.Attack( 0 );
}

