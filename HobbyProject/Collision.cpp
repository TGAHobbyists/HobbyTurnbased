#include "stdafx.h"
#include "collision.h"

#include "terraingrid.h"

Collision::Collision()
{}
Collision::~Collision()
{}

void Collision::Init( TerrainGrid* aTerrainGrid )
{
	myTerrain = aTerrainGrid;
}

bool Collision::IsValidMove( Vector2f& aPosition, Vector2f& aWantedChange ) const
{
	Vector2f newPosition( aPosition + aWantedChange );
	return myTerrain->GetTileAt( newPosition ).myIsSolid == false;
}
bool Collision::IsValidMoveFat( Vector2f& aPosition, Vector2f& aWantedChange, float aFatFactor ) const
{
	Vector2f newPosition( aPosition + aWantedChange );
	
	newPosition.myX -= aFatFactor;
	if( myTerrain->GetTileAt( newPosition ).myIsSolid == true )
		return false;
	newPosition.myX += aFatFactor*2;
	if( myTerrain->GetTileAt( newPosition ).myIsSolid == true )
		return false;

	return true;
}

CU::GrowingArray< Tile > Collision::GetTilesInRange( const Vector2f& aPosition, float aHeight )
{
	CU::GrowingArray< Tile > nearbyTiles;
	nearbyTiles.Init( 16, 32 );

	Tile& originTile = myTerrain->GetTileAt( aPosition );
	nearbyTiles.Add( originTile );
	nearbyTiles.Add( myTerrain->GetTileRightOf( originTile ) );
	nearbyTiles.Add( myTerrain->GetTileLeftOf( originTile ) );

	Tile& addedTile = myTerrain->GetTileBelow( originTile );
	nearbyTiles.Add( addedTile );
	nearbyTiles.Add( myTerrain->GetTileRightOf( addedTile ) );
	nearbyTiles.Add( myTerrain->GetTileLeftOf( addedTile ) );

	addedTile = myTerrain->GetTileAbove( originTile );

	while( aHeight >= 0 )
	{
		nearbyTiles.Add( addedTile );
		nearbyTiles.Add( myTerrain->GetTileRightOf( addedTile ) );
		nearbyTiles.Add( myTerrain->GetTileLeftOf( addedTile ) );
		addedTile = myTerrain->GetTileAbove( addedTile );
		aHeight -= myTerrain->ourTileSize;
	}
	return nearbyTiles;
}
Tile& Collision::GetTileInDirection( const Vector2f& aPosition, const Vector2f& aDirection )
{
	Vector2f newPosition( aPosition + aDirection );
	return myTerrain->GetTileAt( newPosition );
}
