#ifndef _TERRAIN_GRID_H_
#define _TERRAIN_GRID_H_

#include "cu_growingarray.h"
#include "tile.h"

class TerrainGrid
{
public:
	TerrainGrid();
	~TerrainGrid();

	void Init();

	void Render();

	Tile& GetTileAt( const Vector2f& aPositionInGrid );

	Tile& GetTileRightOf( Tile& aTile );
	Tile& GetTileAbove( Tile& aTile );
	Tile& GetTileLeftOf( Tile& aTile );
	Tile& GetTileBelow( Tile& aTile );
	
	static const float ourTileSize;

private:
	static const int ourTileGridSizeX = 100;
	static const int ourTileGridSizeY = 100;
	int GetIndexFromPosition( const Vector2f& aPosition ) const;
	//CU::GrowingArray<Chuck> chunk has tiles!
	CU::GrowingArray< Tile > myTiles;

};

#endif//_TERRAIN_GRID_H_
