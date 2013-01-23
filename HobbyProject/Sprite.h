#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "vector.h"

#include "hgeSprite.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	Sprite operator=( int aSpriteIndex );

	void GetPosition( Vector2f& outPosition );
	void SetPosition( const Vector2f& aNewPosition );

	void SetSize( const Vector2f& aSize );
	const Vector2f& GetSize();

	int GetSpriteIndex();

private:
	Vector2f myPosition;
	Vector2f mySize;
	int mySpriteIndex;
};

#endif//_SPRITE_H_
