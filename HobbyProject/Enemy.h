#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Actor.h"
#include "sprite.h"
#include "AABB2D.h"
class Collision;
#include "AttackComponent.h"

class Enemy : public Actor
{
public:
	Enemy();
	~Enemy();

	void SpawnAt( const Vector2f& vSpawnPosition );
	void Init();
	void Destroy();

	void Update( float aDeltaTime, Collision* aCollisionChecker );
	void UpdateIntelligence( float aDeltaTime );
	void Render();

	Vector2f GetMiddlePosition() const { return myCollisionObject.GetMiddlePosition(); }
	Vector2f GetPosition() const { return myCollisionObject.myPosition; }

	void Jump();
	bool IsInAir() const;
	void Attack();

private:
	Sprite mySprite;
	Vector2f myMovement;
	AABB2D myCollisionObject;
	Hitbox myHitbox;

	Sprite debugsprite;
	float myLastMovementDirection;
};


#endif//_ENEMY_H_
