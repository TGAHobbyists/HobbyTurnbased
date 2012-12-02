#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "vector.h"
class TerrainGrid;

class Collision
{
public:
	Collision();
	~Collision();

	void Init( TerrainGrid* aTerrainGrid );

	bool IsValidMove( Vector2f& aPosition, Vector2f& aWantedChange ) const;

private:
	TerrainGrid* myTerrain;

};

#endif//_COLLISION_H_
