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
	myPosition = Vector2f( 20,0);
	Vector2f unitSize = Vector2f(16,32);
	mySprite.SetTexture( Renderer::GetInstance()->CreateTexture( "Sprites//Unit//Unit.png" ), unitSize );
	myOffset = Vector2f( mySprite.GetRawSprite()->GetWidth()/2, mySprite.GetRawSprite()->GetHeight() );
}

void Unit::Update( float aDeltaTime, Collision* aCollisionChecker )
{
	Vector2f change( 0.f, 19.42f * aDeltaTime );
	Vector2f actualPosition = myPosition;
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
