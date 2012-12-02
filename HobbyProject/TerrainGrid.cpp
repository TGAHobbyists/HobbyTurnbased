#include "stdafx.h"
#include "terraingrid.h"

#include "renderer.h"

const float TerrainGrid::ourTileSize = 16.0f;

TerrainGrid::TerrainGrid()
{

}
TerrainGrid::~TerrainGrid()
{

}

void TerrainGrid::Init()
{
	myTiles.Init(ourTileGridSizeX * ourTileGridSizeY, 1000);

	Vector2f pos;
	Vector2f tileSize(ourTileSize, ourTileSize);

	int index = 0;
	for( index; index < ourTileGridSizeX * 10; ++index )
	{
		myTiles.Add( Tile() );
		myTiles[index].mySprite.SetTexture( 0, tileSize );
		pos = Vector2f( ourTileSize * (index % ourTileGridSizeX), ourTileSize * (index / ourTileGridSizeX));
		myTiles[index].mySprite.SetPosition( pos );
		myTiles[index].myIsSolid = false;
	}
	for( index; index < ourTileGridSizeX * ourTileGridSizeY; ++index )
	{
		myTiles.Add( Tile() );
		myTiles[index].mySprite.SetTexture( Renderer::GetInstance()->CreateTexture( "Sprites//Terrain//Grass.bmp" ), tileSize );
		pos = Vector2f( ourTileSize * (index % ourTileGridSizeX), ourTileSize * (index / ourTileGridSizeX));
		myTiles[index].mySprite.SetPosition( pos );
		myTiles[index].myIsSolid = true;
	}
}
void TerrainGrid::Render()
{
	for( int index = 0; index < ourTileGridSizeX * ourTileGridSizeY; ++index )
	{
		Renderer::GetInstance()->SpriteRender( &myTiles[index].mySprite );
	}
}
Tile& TerrainGrid::GetTileAt( Vector2f& aPositionInGrid )
{
	return myTiles[ GetIndexFromPosition( aPositionInGrid ) ];
}
int TerrainGrid::GetIndexFromPosition( Vector2f& aPosition ) const
{
	int x = static_cast<int>(aPosition.myX / ourTileSize);
	int y = static_cast<int>(aPosition.myY / ourTileSize);
	int index = x + (y * ourTileGridSizeX);
	return CU::Macro::Clamp( index, 0, ourTileGridSizeX * ourTileGridSizeY );;
}
