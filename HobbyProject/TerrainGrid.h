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

private:
	//CU::GrowingArray<Chuck> chunk has tiles!
	CU::GrowingArray< Tile > myTiles;

};

#endif//_TERRAIN_GRID_H_
