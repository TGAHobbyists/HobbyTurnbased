#ifndef _HITBOX_H_
#define _HITBOX_H_

#include "AABB2D.h"
// intent:
// wraps several AABB2D and/or circles as hitboxes
// holds a single callback for what happens if one is hit
// if any box is hit it will return the index to said box
// and use that as an argument to the callback
class Hitbox
{
public:
	Hitbox() {}
	~Hitbox() {}

	AABB2D& GetHitbox() { return myCollisionObject; }

private:
	//Vector of boxes not just one
	AABB2D myCollisionObject;
};


#endif//_HITBOX_H_
