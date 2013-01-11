#include "stdafx.h"
#include "sprite.h"

Sprite::Sprite()
{
	mySprite = NULL;
}
Sprite::~Sprite()
{

}

void Sprite::GetPosition( Vector2f& outPosition )
{
	outPosition = myPosition;
}
void Sprite::SetPosition( const Vector2f& aNewPosition )
{
	myPosition = aNewPosition;
}

void Sprite::SetTexture( HTEXTURE aNewTexture, Vector2f& aSize )
{
	if( mySprite == NULL )
	{
		mySprite = new hgeSprite( aNewTexture, myPosition.myX, myPosition.myY, aSize.x, aSize.y );
	}
	else
	{
		SAFE_DELETE( mySprite );
		mySprite = new hgeSprite( aNewTexture, myPosition.myX, myPosition.myY, aSize.x, aSize.y );
	}
}
