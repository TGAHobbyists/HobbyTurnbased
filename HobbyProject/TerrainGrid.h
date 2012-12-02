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

	Tile& GetTileAt( Vector2f& aPositionInGrid );
	

private:
	static const int ourTileGridSizeX = 100;
	static const int ourTileGridSizeY = 100;
	static const float ourTileSize;
	int GetIndexFromPosition( Vector2f& aPosition ) const;
	//CU::GrowingArray<Chuck> chunk has tiles!
	CU::GrowingArray< Tile > myTiles;

};

#endif//_TERRAIN_GRID_H_
