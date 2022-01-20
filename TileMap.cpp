#include "TileMap.h"

TileMap::TileMap(const char* file, int width, int height)
	: tileSurface(file)
	, width(width)
	, height(height)
	, tiles(width * height)
{}

const Tile& TileMap::GetTile(int x, int y) const
{
	int i = x + y * width;
	return tiles[i];
}

void TileMap::SetTile(int x, int y, const Tile& tile)
{
	int i = x + y * width;
	tiles[i] = tile;
}

void TileMap::SetTiles(const std::vector<Tile>& tiles)
{
	this->tiles = tiles;
}

void TileMap::Draw(Tmpl8::Surface& screen, int xoffset, int yoffset)
{
	// TODO: Copy the tiles according the tiles array!
	tileSurface.CopyTo(&screen, xoffset, yoffset);
}
