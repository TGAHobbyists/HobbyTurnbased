#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "vector.h"

#include "hgeSprite.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void GetPosition( Vector2f& outPosition );
	void SetPosition( const Vector2f& aNewPosition );

	void SetTexture( HTEXTURE aNewTexture, Vector2f& aSize );
	hgeSprite* GetRawSprite() { return mySprite; }
	void SetSize( const Vector2f& aSize );

private:
	hgeSprite* mySprite;
	Vector2f myPosition;
};

#endif//_SPRITE_H_
