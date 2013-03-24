#ifndef _AXIS_ALIGNED_BOUNDING_BOX_2D_H_
#define _AXIS_ALIGNED_BOUNDING_BOX_2D_H_

#include "CollisionObject.h"
#include "Vector.h"

typedef AxisAlignedBoundingBox2D AABB2D;

class AxisAlignedBoundingBox2D: public CollisionObject
{
public:
	AxisAlignedBoundingBox2D() {}
	~AxisAlignedBoundingBox2D() {}

	//Collision interface
	bool CollideWith( CollisionObject* aCollisionObject );

	bool CollideWith( AABB2D* aAlignedBox );




	//-------------------------------------------------------------------------
	Vector2f GetMinPosition() const { return myPosition + myMinOffset; }
	Vector2f GetMaxPosition() const { return myPosition + myMaxOffset; }
	Vector2f GetMiddlePosition() const { return myPosition + ((myMinOffset + myMaxOffset) * 0.5f); }
	Vector2f GetSize() const { return myMaxOffset - myMinOffset; }

	Vector2f myPosition;
	Vector2f myMinOffset;
	Vector2f myMaxOffset;

private:

};

#endif//_AXIS_ALIGNED_BOUNDING_BOX_H_
