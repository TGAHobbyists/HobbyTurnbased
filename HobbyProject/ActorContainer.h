#ifndef _ACTOR_CONTAINER_H_
#define _ACTOR_CONTAINER_H_

#include "Actor.h"

class ActorContainer
{
public:
	ActorContainer();
	~ActorContainer();

	static ActorContainer* GetInstance();

	void								RegisterActor( Actor* pActorToRegister );
	void								UnRegisterActor( Actor* pActorToUnRegister );
	const CU::GrowingArray< Actor* >&	GetActors();
	const Actor*						GetAvatar();
	// lolhack
	void								SetEnemyTarget( const Vector2f& vTarget );
	const Vector2f&						GetEnemyTarget();


private:
	static ActorContainer* ourInstance;
	CU::GrowingArray< Actor* >	myActors;
	Actor*						myAvatarPointer;
	Vector2f					m_vEnemyTarget;
};


#endif//_ACTOR_CONTAINER_H_
