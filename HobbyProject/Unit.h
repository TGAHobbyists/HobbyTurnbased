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

	void Update( float aDeltaTime, Collision* aCollisionChecker );
	void Render();

	void StartMoveRight();
	void StopMoveRight();
	void StartMoveLeft();
	void StopMoveLeft();
	void Jump();
	bool IsInAir() const;
private:
	Sprite mySprite;
	Vector2f myPosition;
	Vector2f myOffset;
	Vector2f myMovement;
};



#endif//_UNIT_H_
