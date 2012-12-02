#include "stdafx.h"
#include "terraingrid.h"

#include "renderer.h"

TerrainGrid::TerrainGrid()
{

}
TerrainGrid::~TerrainGrid()
{

}

void TerrainGrid::Init()
{
	myTiles.Init(100 * 100, 1000);

	Vector2f pos;

	int index = 0;
	for( index; index < 100*10; ++index )
	{
		myTiles.Add( Tile() );
		myTiles[index].mySprite.SetTexture( 0 );
		pos = Vector2f( 16.f * (index % 100), 16.f * (index / 100));
		myTiles[index].mySprite.SetPosition( pos );
	}
	for( index; index < 100*100; ++index )
	{
		myTiles.Add( Tile() );
		myTiles[index].mySprite.SetTexture( Renderer::GetInstance()->CreateTexture( "Sprites//Terrain//Grass.bmp" ) );
		pos = Vector2f( 16.f * (index % 100), 16.f * (index / 100));
		myTiles[index].mySprite.SetPosition( pos );
	}
}
void TerrainGrid::Render()
{
	for( int index = 0; index < 100 * 100; ++index )
	{
		Renderer::GetInstance()->SpriteRender( &myTiles[index].mySprite );
	}
}

