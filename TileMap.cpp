#include "TileMap.h"

using namespace Tmpl8;

TileMap::TileMap(const char* file)
	: tileSurface(file)
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

void TileMap::SetTiles(const std::vector<Tile>& tiles, int width)
{
	this->width = width;
	this->tiles = tiles;
}

void TileMap::DrawTile(Tmpl8::Surface& screen, const Tile& tile, int tileX, int tileY)
{
	int dstX = offset.x + (tileX * tile.width);
	int dstY = offset.y + (tileY * tile.height);
	int srcX = tile.x  * ( tile.width + 1 ) + 1;
	int srcY = tile.y * ( tile.height + 1 ) + 1;

	Pixel* dst = screen.GetBuffer() + dstX + dstY * screen.GetPitch();
	Pixel* src = tileSurface.GetBuffer() + srcX + srcY * tileSurface.GetPitch();

	for (int y = 0; y < tile.height; ++y)
	{
		// TODO: Clipping.
		memcpy(dst, src, sizeof(Pixel) * tile.width);
		dst += screen.GetPitch();
		src += tileSurface.GetPitch();
	}
}


void TileMap::Draw(Tmpl8::Surface& screen)
{
	int tileX = 0;
	int tileY = 0;
	for (auto& tile : tiles)
	{
		DrawTile(screen, tile, tileX, tileY);
		++tileX;
		if (tileX >= width)
		{
			tileX = 0;
			++tileY;
		}
	}
}
