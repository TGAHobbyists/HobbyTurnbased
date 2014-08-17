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
	void Attack();

	bool IsAvatar() { return true; }

	void onHit( Hitbox* pEnemyHitbox );

private:
	Sprite mySprite;

	Vector2f myMovement;
	Vector2f myExternalVelocities;
	AABB2D myCollisionObject;
	Hitbox myHitbox;

	float myInvulnerabilityTime;

	int m_iHealth;

	Sprite debugsprite;
	AttackComponent myAttackComponent;
	float myLastMovementDirection;
};



#endif//_UNIT_H_
