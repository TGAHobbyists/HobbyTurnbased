#include "stdafx.h"
#include "Actor.h"

#include "ActorContainer.h"


void Actor::Init()
{
	ActorContainer* pActorContainer = ActorContainer::GetInstance();
	assert( pActorContainer );

	pActorContainer->RegisterActor( this );
}

void Actor::Destroy()
{
	ActorContainer* pActorContainer = ActorContainer::GetInstance();
	assert( pActorContainer );

	pActorContainer->UnRegisterActor( this );
}
