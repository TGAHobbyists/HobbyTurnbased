#include "stdafx.h"
#include "avatar.h"

#include "renderer.h"
#include "collision.h"

#include "tile.h"

Avatar::Avatar()
{}
Avatar::~Avatar()
{
	Destroy();
}

void Avatar::Init()
{
	myMovement.myY = 19.42f;
	myLastMovementDirection = 1.0f;
	myCollisionObject.myPosition = Vector2f( 25,5);
	mySprite = Renderer::GetInstance()->CreateTexture( "Sprites//Unit//Unit.png" );
	myCollisionObject.myMinOffset = Vector2f( mySprite.GetSize().x * -0.5f, mySprite.GetSize().y * -1.f );
	myCollisionObject.myMaxOffset = Vector2f( mySprite.GetSize().x * 0.5f, 0 );

	myHitbox.GetHitbox() = myCollisionObject;
	myHitbox.setCallback( fastdelegate::MakeDelegate( this, &Avatar::onHit ) );
	myHitbox.myAlignment = Hitbox::ALIGNMENT_PLAYER;
	Collision::GetInstance()->AddHitbox( &myHitbox );

	Vector2f debufsize(32,32);
	debugsprite = Renderer::GetInstance()->CreateTexture( "Sprites//Hitbox.png" );
	debugsprite.SetSize( myCollisionObject.GetSize() );
	myAttackComponent.Init();
	myAttackComponent.AddAttack();
	m_iHealth = 100;
	Actor::Init();
}

void Avatar::Destroy()
{
	Actor::Destroy();
}

void Avatar::Update( float aDeltaTime, Collision* aCollisionChecker )
{
	myInvulnerabilityTime -= aDeltaTime;
	
	if( !IsInAir() )
	{
		const float fDecelerationFactor = 800.f;
		float fNewLength = CU::Macro::Max( 0.0f, myExternalVelocities.Length() - fDecelerationFactor * aDeltaTime );
		myExternalVelocities = myExternalVelocities.Normalize() * fNewLength;
	}
	// movement update
	myMovement.myY += (9.82f) * 40.f * aDeltaTime;
	Vector2f change = Vector2f( 0, ( myExternalVelocities.myY + myMovement.myY ) * aDeltaTime );
	if( !aCollisionChecker->IsValidMoveFat( myCollisionObject.myPosition, change, 7.f ) )
	{
		myMovement.myY = 0;
		myExternalVelocities.myY = 0;
	}
	change = ( myExternalVelocities + myMovement ) * aDeltaTime;
	if( !aCollisionChecker->IsValidMoveFat( myCollisionObject.myPosition, change, 7.f ) )
	{
		change.myX = 0;
	}
	if( change.myX > 0 )
		myLastMovementDirection = 1.0f;
	else if( change.myX < 0 )
		myLastMovementDirection = -1.f;
	myCollisionObject.myPosition += change;
	// alignSprites
	myHitbox.GetHitbox().myPosition = GetPosition();
	mySprite.SetPosition( myCollisionObject.GetMinPosition() );
	debugsprite.SetPosition( myCollisionObject.GetMinPosition() );
	// attacking
	myAttackComponent.Update( aDeltaTime, myCollisionObject.myPosition, myLastMovementDirection );
}
void Avatar::Render()
{
	Renderer::GetInstance()->SpriteRender( &mySprite );
	//myAttackComponent.DEBUGRender();
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

void Avatar::Attack()
{
	myAttackComponent.Attack( 0 );
}

void Avatar::onHit( Hitbox* pEnemyHitbox )
{
	if( myInvulnerabilityTime <= 0.0f && pEnemyHitbox != NULL && pEnemyHitbox->myAlignment != myHitbox.myAlignment )
	{
		myInvulnerabilityTime = 0.8f;
		const bool bToRightOf = myHitbox.GetHitbox().GetMiddlePosition().x > pEnemyHitbox->GetHitbox().GetMiddlePosition().x;
		Vector2f vLaunchVector = Vector2f( 10, -5 ).Normalize();
		if( !bToRightOf )
			vLaunchVector.x *= -1;
		vLaunchVector = vLaunchVector * 150.f;
		myMovement.myY = vLaunchVector.myY;
		myExternalVelocities.myX += vLaunchVector.myX;
	}
}
