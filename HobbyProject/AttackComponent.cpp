#include "stdafx.h"
#include "AttackComponent.h"

#include "Renderer.h"
#include "Collision.h"

AttackComponent::AttackComponent()
: myAttackTime( 0.0f )
{

}

AttackComponent::~AttackComponent()
{

}

void AttackComponent::Init()
{

}
void AttackComponent::Update( const float aDeltaTime, const Vector2f& aParentPosition, const float aFacing )
{
	myHitbox.GetHitbox().myPosition = aParentPosition + Vector2f( myOffset.x * aFacing, myOffset.y );
	myHitbox.myAlignment = Hitbox::ALIGNMENT_PLAYER;

	Vector2f position = myHitbox.GetHitbox().myPosition - myHitbox.GetHitbox().GetSize() * 0.5f;

	mySprite.SetPosition( position );

	if( myAttackTime > 0.0f )
	{
		myAttackTime -= CU::Macro::Min( aDeltaTime, myAttackTime );
		if( myAttackTime == 0.0f )
			Collision::GetInstance()->RemoveHitbox( &myHitbox );
	}

}

void AttackComponent::AddAttack( /* fastdelegate to call when attack hits*/ /* hitbox info from loaded file */ )
{
	myOffset = Vector2f( 6.f, -16.f );
	myHitbox.GetHitbox().myMinOffset = Vector2f( -8.f, -16.f );
	myHitbox.GetHitbox().myMaxOffset = Vector2f( 8.f, 16.f );
	

	mySprite = Renderer::GetInstance()->CreateTexture( "Sprites//Hitbox.png" );
	mySprite.SetSize( myHitbox.GetHitbox().GetSize() );
}

void AttackComponent::Attack( int anAttackNumber )
{
	anAttackNumber;
	if( myAttackTime == 0.0f )
		Collision::GetInstance()->AddHitbox( &myHitbox );
	myAttackTime = 0.5f;
	
}

void AttackComponent::DEBUGRender()
{
	if( myAttackTime > 0.0f )
	Renderer::GetInstance()->SpriteRender( &mySprite );
}

