#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "vector.h"
#include "cu_growingarray.h"
#include "tile.h"
class TerrainGrid;

class Collision
{
public:
	Collision();
	~Collision();

	void Init( TerrainGrid* aTerrainGrid );

	bool IsValidMove( Vector2f& aPosition, Vector2f& aWantedChange ) const;
	bool IsValidMoveFat( Vector2f& aPosition, Vector2f& aWantedChange, float aFatFactor ) const;

	CU::GrowingArray< Tile > GetTilesInRange( const Vector2f& aPosition, float aHeight );
	Tile& GetTileInDirection( const Vector2f& aPosition, const Vector2f& aDirection );
	Tile& GetTileAt( const Vector2f& aPosition );

private:
	TerrainGrid* myTerrain;

};

#endif//_COLLISION_H_
