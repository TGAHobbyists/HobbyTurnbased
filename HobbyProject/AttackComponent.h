#ifndef _ATTACK_COMPONENT_H_
#define _ATTACK_COMPONENT_H_

#include "Hitbox.h"
#include "Sprite.h"
// intent holds a bunch of different attacks
// can use any depending on a number

class AttackComponent
{
public:
	AttackComponent();
	~AttackComponent();

	void Init();
	// facing > 0 means facing right, < 0 means left
	void Update( const float aDeltaTime, const Vector2f& aParentPosition, const float aFacing );

	void AddAttack( /* fastdelegate to call when attack hits*/ /* hitbox info from loaded file */ );

	void Attack( int anAttackNumber );

	void DEBUGRender();

private:
	Sprite mySprite;
	Vector2f myOffset;
	Hitbox myHitbox;
	float myAttackTime;
	int myCollisionHandle;
};

#endif//_ATTACK_COMPONENT_H_

