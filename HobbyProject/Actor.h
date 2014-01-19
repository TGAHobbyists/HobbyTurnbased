#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "Collision.h"
class Hitbox;

class Actor
{
public:
	Actor()
	{}
	virtual ~Actor()
	{}

	virtual void Init() = 0;
	virtual void Destroy() = 0;

	virtual void Update( float aDeltaTime, Collision* aCollisionChecker ) = 0;

	virtual void Render() = 0;

	virtual bool IsAvatar() { return false; }

	virtual Vector2f GetPosition() const = 0;

private:
	

};

#endif//_ACTOR_H_