#include "stdafx.h"
#include "collision.h"

#include "terraingrid.h"
#include "Renderer.h"

Collision* Collision::ourCollision = NULL;

Collision::Collision() {}
Collision::~Collision() {}

void Collision::Init( TerrainGrid* aTerrainGrid )
{
	myTerrain = aTerrainGrid;
	myHitboxes.Init( 20, 20 );
}

void Collision::Update()
{
	// ugly n^2 complexity
	for( int index = 0; index < myHitboxes.Count(); ++index )
	{
		for( int othersIndex = index + 1; othersIndex < myHitboxes.Count(); ++ othersIndex )
		{
			if( myHitboxes[ index ]->GetHitbox().CollideWith( &myHitboxes[othersIndex]->GetHitbox() ) )
			{
				myHitboxes[ index ]->CollisionWith( myHitboxes[othersIndex] );
				myHitboxes[ othersIndex ]->CollisionWith( myHitboxes[index] );
				// starting to look PRETTY havok
			}
		}
	}
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
	//assert( aDirection.Length2() < 64.f && "Derp" )
	Vector2f newPosition( aPosition + aDirection );
	return myTerrain->GetTileAt( newPosition );

}

Tile& Collision::GetTileAt( const Vector2f& aPosition )
{
	return myTerrain->GetTileAt( aPosition );
}

void Collision::AddHitbox( Hitbox* aHitbox )
{
	myHitboxes.Add( aHitbox );
}

void Collision::Create()
{
	if( ourCollision == NULL )
		ourCollision = new Collision;
}

void Collision::Destroy()
{
	SAFE_DELETE( ourCollision );
}

Collision* Collision::GetInstance()
{
	return ourCollision;
}

void Collision::RemoveHitbox( Hitbox* myHitbox )
{
	for( int index = 0; index < myHitboxes.Count(); ++index )
	{
		if( myHitboxes[index] == myHitbox )
		{
			myHitboxes.RemoveCyclicAtIndex( index );
		}
	}
}

void Collision::RenderDebug()
{
	std::stringstream stringStream;
	stringStream << "Number of hitboxes: ";
	stringStream << myHitboxes.Count();
	Renderer::GetInstance()->TextRender( stringStream.str(), Vector2f( 50.f, 10.f ), ALIGN_LEFT );
}

