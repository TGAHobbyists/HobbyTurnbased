#ifndef _UNIT_H_
#define _UNIT_H_

#include "sprite.h"
class Collision;

class Unit
{
public:
	Unit();
	~Unit();

	void Init();

	void Update( Collision* aCollisionChecker );
	void Render();
private:
	Sprite mySprite;
	Vector2f myPosition;
	Vector2f myOffset;
};



#endif//_UNIT_H_
