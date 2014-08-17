#include "stdafx.h"
#include "Enemy.h"

#include "renderer.h"
#include "collision.h"

#include "tile.h"
#include "ActorContainer.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	Destroy();
}

void Enemy::Init()
{
	myMovement.myY = 19.42f;
	myLastMovementDirection = 1.0f;
	myCollisionObject.myPosition = Vector2f( 25,5);
	mySprite = Renderer::GetInstance()->CreateTexture( "Sprites//Unit//enemy.png" );
	myCollisionObject.myMinOffset = Vector2f( mySprite.GetSize().x * -0.5f, mySprite.GetSize().y * -1.f );
	myCollisionObject.myMaxOffset = Vector2f( mySprite.GetSize().x * 0.5f, 0 );

	myHitbox.GetHitbox() = myCollisionObject;
	myHitbox.myAlignment = Hitbox::ALIGNMENT_HOSTILE;
	Collision::GetInstance()->AddHitbox( &myHitbox );

	//debugsprite = Renderer::GetInstance()->CreateTexture( "Sprites//Hitbox.png" );
	//debugsprite.SetSize( myCollisionObject.GetSize() );
	//myAttackComponent.Init();
	//myAttackComponent.AddAttack();
	Actor::Init();
}

void Enemy::Destroy()
{
	Actor::Destroy();
}

void Enemy::Update( float aDeltaTime, Collision* aCollisionChecker )
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
	myHitbox.GetHitbox().myPosition = GetPosition();
	mySprite.SetPosition( myCollisionObject.GetMinPosition() );
	debugsprite.SetPosition( myCollisionObject.GetMinPosition() );
	//myAttackComponent.Update( aDeltaTime, myCollisionObject.myPosition, myLastMovementDirection );


	// Brain update
	UpdateIntelligence( aDeltaTime );
}

void Enemy::UpdateIntelligence( float aDeltaTime )
{
	aDeltaTime;
	Vector2f vTarget = ActorContainer::GetInstance()->GetEnemyTarget() - myHitbox.GetHitbox().myPosition;
	

	if( vTarget.x > 3.0f )
	{
		myMovement.myX = 100.f;
	}
}

void Enemy::Render()
{
	Renderer::GetInstance()->SpriteRender( &mySprite );
	
	Renderer::GetInstance()->SpriteRender( &debugsprite );
}

void Enemy::Jump()
{
	if( !IsInAir() )
		myMovement.myY = -20.f;
}

bool Enemy::IsInAir() const
{
	return myMovement.myY != 0;
}

void Enemy::Attack()
{
	//myAttackComponent.Attack( 0 );
}

void Enemy::SpawnAt( const Vector2f& vSpawnPosition )
{
	Init();
	myCollisionObject.myPosition = vSpawnPosition;
}

