#include "stdafx.h"
#include "AABB2D.h"



bool AxisAlignedBoundingBox2D::CollideWith( CollisionObject* aCollisionObject )
{
	return aCollisionObject->CollideWith( this );
}

bool AxisAlignedBoundingBox2D::CollideWith( AABB2D* aAlignedBox )
{
	Vector2f minPos( myPosition + myMinOffset + aAlignedBox->myMinOffset );
	Vector2f maxPos( myPosition + myMaxOffset + aAlignedBox->myMaxOffset );

	if( aAlignedBox->myPosition.myX > maxPos.myX ) return false;
	if( aAlignedBox->myPosition.myX < minPos.myX ) return false;
	if( aAlignedBox->myPosition.myY > maxPos.myY ) return false;
	if( aAlignedBox->myPosition.myY > minPos.myY ) return false;
	return false;
}
