#ifndef _UNIT_H_
#define _UNIT_H_

#include "Actor.h"
#include "sprite.h"
#include "AABB2D.h"
class Collision;
#include "AttackComponent.h"

class Avatar: public Actor
{
public:
	Avatar();
	~Avatar();

	void Init();
	void Destroy();

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

	bool IsAvatar() { return true; }

	void onHit();

private:
	Sprite mySprite;
	//Vector2f myOffset;
	Vector2f myMovement;
	AABB2D myCollisionObject;
	Hitbox myHitbox;

	Sprite debugsprite;
	AttackComponent myAttackComponent;
	float myLastMovementDirection;
};



#endif//_UNIT_H_
