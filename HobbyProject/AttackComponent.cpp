#include "stdafx.h"
#include "AttackComponent.h"

#include "Renderer.h"

AttackComponent::AttackComponent()
{

}

AttackComponent::~AttackComponent()
{

}

void AttackComponent::Init()
{

}
void AttackComponent::Update( const Vector2f& aParentPosition, const float aFacing )
{
	myHitbox.GetHitbox().myPosition = aParentPosition + Vector2f( myOffset.x * aFacing, myOffset.y );
}

void AttackComponent::AddAttack( /* fastdelegate to call when attack hits*/ /* hitbox info from loaded file */ )
{
	myOffset = Vector2f( 16.f, -16.f );
	myHitbox.GetHitbox().myMinOffset = Vector2f( -16.f, -8.f );
	myHitbox.GetHitbox().myMaxOffset = Vector2f( 16.f, 8.f );

	mySprite = Renderer::GetInstance()->CreateTexture( "Sprites//Hitbox.png" );
	mySprite.SetSize( myHitbox.GetHitbox().GetSize() );
}

void AttackComponent::Attack( int anAttackNumber )
{
	anAttackNumber;
}

void AttackComponent::DEBUGRender()
{
	Renderer::GetInstance()->SpriteRender( &mySprite );
}

