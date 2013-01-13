#ifndef _UNIT_H_
#define _UNIT_H_

#include "sprite.h"
#include "AABB2D.h"
class Collision;

class Unit
{
public:
	Unit();
	~Unit();

	void Init();

	void Update( float aDeltaTime, Collision* aCollisionChecker );
	void Render();

	void StartMoveRight();
	void StopMoveRight();
	void StartMoveLeft();
	void StopMoveLeft();
	void Jump();
	bool IsInAir() const;
	void DEBUGDigDown( Collision* aCollision );
private:
	Sprite mySprite;
	//Vector2f myOffset;
	Vector2f myMovement;
	AABB2D myCollisionObject;
};



#endif//_UNIT_H_
