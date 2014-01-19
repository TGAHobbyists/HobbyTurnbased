#include "stdafx.h"
#include "ActorContainer.h"

ActorContainer* ActorContainer::ourInstance = NULL;

ActorContainer::ActorContainer()
{
	ourInstance = this;
	myActors.Init( 32, 64 );
	myAvatarPointer = NULL;
}

ActorContainer::~ActorContainer()
{
	ourInstance = NULL;
}

ActorContainer* ActorContainer::GetInstance()
{
	return ourInstance;
}

void ActorContainer::RegisterActor( Actor* pActorToRegister )
{
	if( pActorToRegister->IsAvatar() )
	{
		myAvatarPointer = pActorToRegister;
	}
	myActors.Add( pActorToRegister );
}

void ActorContainer::UnRegisterActor( Actor* pActorToUnRegister )
{
	for( int index = myActors.Count() - 1; index >= 0 ; --index )
	{
		if( myActors[index] == pActorToUnRegister )
			myActors.RemoveCyclicAtIndex( index );
	}
}

const CU::GrowingArray< Actor* >& ActorContainer::GetActors()
{
	return myActors;
}

const Actor* ActorContainer::GetAvatar()
{
	return myAvatarPointer;
}
