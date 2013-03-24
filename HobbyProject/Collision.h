#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "vector.h"
#include "cu_growingarray.h"
#include "tile.h"
#include "Hitbox.h"
class TerrainGrid;

class Collision
{
public:
	static Collision* GetInstance();
	static void Create();
	static void Destroy();

	Collision();
	~Collision();

	void Init( TerrainGrid* aTerrainGrid );

	void Update();

	bool IsValidMove( Vector2f& aPosition, Vector2f& aWantedChange ) const;
	bool IsValidMoveFat( Vector2f& aPosition, Vector2f& aWantedChange, float aFatFactor ) const;

	CU::GrowingArray< Tile > GetTilesInRange( const Vector2f& aPosition, float aHeight );
	Tile& GetTileInDirection( const Vector2f& aPosition, const Vector2f& aDirection );
	Tile& GetTileAt( const Vector2f& aPosition );

	void AddHitbox( Hitbox* aHitbox );
	void RemoveHitbox( Hitbox* myHitbox );
	
	void RenderDebug();

private:



	static Collision* ourCollision;

	TerrainGrid* myTerrain;
	CU::GrowingArray< Hitbox* > myHitboxes;

};

#endif//_COLLISION_H_
