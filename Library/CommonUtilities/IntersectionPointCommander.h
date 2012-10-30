#ifndef _INTERSECTION_POINT_COMMANDER_H_
#define _INTERSECTION_POINT_COMMANDER_H_

#include "Vector.h"

class IntersectionPointCommander
{
public:
	IntersectionPointCommander(void);
	virtual ~IntersectionPointCommander(void);

	virtual void Execute(Vector3f anIntersectionPoint) = 0;
};

#endif//_INTERSECTION_POINT_COMMANDER_H_

