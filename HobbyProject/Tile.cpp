#include "stdafx.h"
#include "tile.h"

Tile::Tile()
{

}
Tile::~Tile()
{

}


void Tile::Strike( int aDamage )
{
	myDurability -= aDamage;
	if( myDurability <= 0 )
		myIsSolid = false;
	Vector2f size( 16, 16 );
	mySprite.SetTexture( 0, size );
}

