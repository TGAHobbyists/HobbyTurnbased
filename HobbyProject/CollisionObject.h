#ifndef _COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_

class AxisAlignedBoundingBox2D;

class CollisionObject
{
public:
	CollisionObject() {}
	~CollisionObject() {}

	virtual bool CollideWith( CollisionObject* aCollisionObject ) = 0;

	virtual bool CollideWith( AxisAlignedBoundingBox2D* aAlignedBox ) = 0;
};


#endif//_COLLISION_INTERFACE_2D_H_
