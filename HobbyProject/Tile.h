#ifndef _TILE_H_
#define _TILE_H_

#include "sprite.h"

class Tile
{
public:
	Tile();
	~Tile();

	void Strike( int aDamage );

	int myDurability;
	int myMaxDurability;
	bool myIsSolid;
	Sprite mySprite;
private:

};


#endif//_TILE_H_
