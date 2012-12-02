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
