#include "stdafx.h"

#include "Hitbox.h"



bool Hitbox::setCallback( CollisionCallback aCollisionCallback )
{
	if( myCallback.empty() )
	{
		myCallback = aCollisionCallback;
		return true;
	}
	return false;
}
