#ifndef _UNIT_H_
#define _UNIT_H_

#include "sprite.h"
#include "AABB2D.h"
class Collision;

class Avatar
{
public:
	Avatar();
	~Avatar();

	void Init();

	void Update( float aDeltaTime, Collision* aCollisionChecker );
	void Render();

	Vector2f GetMiddlePosition() const { return myCollisionObject.GetMiddlePosition(); }
	Vector2f GetPosition() const { return myCollisionObject.myPosition; }

	void StartMoveRight();
	void StopMoveRight();
	void StartMoveLeft();
	void StopMoveLeft();
	void Jump();
	bool IsInAir() const;
	void DEBUGDigDown( Collision* aCollision );
	void DigInDirection( Vector2f aDirection, Collision* aCollision );
	void Attack();
private:
	Sprite mySprite;
	//Vector2f myOffset;
	Vector2f myMovement;
	AABB2D myCollisionObject;
	Sprite debugsprite;
};



#endif//_UNIT_H_
