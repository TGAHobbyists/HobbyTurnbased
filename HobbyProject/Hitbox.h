#ifndef _HITBOX_H_
#define _HITBOX_H_

#include "CollisionLayers.h"
#include "AABB2D.h"
#include "FastDelegate.h"
// intent:
// wraps several AABB2D and/or circles as hitboxes
// holds a single callback for what happens if one is hit
// if any box is hit it will return the index to said box
// and use that as an argument to the callback


class Hitbox
{
public:
	typedef fastdelegate::FastDelegate0< void > CollisionCallback;
	enum HitboxType
	{
		TYPE_BODY,
		TYPE_ATTACK,
		TYPE_UNDEFINED,
	};
	enum HitboxAlignment
	{
		ALIGNMENT_PLAYER,
		ALIGNMENT_HOSTILE,
		ALIGNMENT_GLOBAL,
	};
	Hitbox(): myLayer( LAYER_EVERYTHING ), myType( TYPE_UNDEFINED ), myAlignment( ALIGNMENT_GLOBAL ) {}
	~Hitbox() {}

	bool	setCallback( CollisionCallback aCollisionCallback );

	AABB2D& GetHitbox() { return myCollisionObject; }

	HitboxType myType;
	HitboxAlignment myAlignment;

	CollisionCallback myCallback;
private:
	//Vector of boxes not just one
	AABB2D myCollisionObject;
	CollisionLayer myLayer;
};

#endif//_HITBOX_H_
