#ifndef _SPRITE_CONTAINER_H_
#define _SPRITE_CONTAINER_H_

#include "CU_GrowingArray.h"

class hgeSprite;
class HGE;
class Renderer;

class SpriteContainer
{
public:
	SpriteContainer();
	~SpriteContainer();

	void Init( HGE* aHGE );
	const int GetSprite( const std::string& aSprite );
private:
	
	friend class Renderer;

	struct Sprites
	{
		std::string myName;
		hgeSprite* mySprite;
	};

	HGE* myHge;
	CU::GrowingArray< Sprites > mySprites;
};

#endif // _SPRITE_CONTAINER_H_