#include "stdafx.h"
#include "sprite.h"
#include "renderer.h"

Sprite::Sprite()
: mySpriteIndex( -1 )
{}

Sprite::~Sprite()
{

}

Sprite Sprite::operator =(int aSpriteIndex)
{
	mySpriteIndex = aSpriteIndex;
	myPosition = myPosition;
	mySize = Renderer::GetInstance()->GetSpriteSize( mySpriteIndex );

	return ( *this );
}

void Sprite::GetPosition( Vector2f& outPosition )
{
	outPosition = myPosition;
}
void Sprite::SetPosition( const Vector2f& aNewPosition )
{
	myPosition = aNewPosition;
}

void Sprite::SetSize( const Vector2f& aSize )
{
	mySize = aSize;
}

const Vector2f& Sprite::GetSize()
{
	return mySize;
}

int Sprite::GetSpriteIndex()
{
	return mySpriteIndex;
}

