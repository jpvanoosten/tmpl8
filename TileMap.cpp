#include "TileMap.h"

using namespace Tmpl8;

TileMap::TileMap(const char* file)
	: tileSurface(file)
	, width(0)
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

bool TileMap::Collides(const Tmpl8::vec2& p) const
{
	Tmpl8::vec2 localPoint = p - offset;

	return false;
}

bool TileMap::Collides(const Bounds& bounds) const
{
	if (tiles.empty()) return false;

	int tileWidth = tiles[0].width;
	int tileHeight = tiles[0].height;

	// TODO: Loop through the points of the bb and check for collisions.
}


void TileMap::DrawTile(Tmpl8::Surface& screen, const Tile& tile, int tileX, int tileY)
{
	int dstW = tile.width;
	int dstH = tile.height;
	int dstX = static_cast<int>(offset.x + (tileX * tile.width));
	int dstY = static_cast<int>(offset.y + (tileY * tile.height));

	int srcX = tile.x  * ( tile.width + 1 ) + 1;
	int srcY = tile.y * ( tile.height + 1 ) + 1;

	// Compute the amount to clip.
	int clipLeft = std::min(0, dstX);
	int clipTop = std::min(0, dstY);		
	int clipRight = std::max(0, dstX + dstW - screen.GetWidth());
	int clipBottom = std::max(0, dstY + dstH - screen.GetHeight());

	// Adjust the source and destination rectangles according to the clipping.
	dstX -= clipLeft;
	dstY -= clipTop;
	dstW -= clipRight;
	dstH -= clipBottom;
	srcX -= clipLeft;
	srcY -= clipTop;

	// Check if the entire tile is clipped.
	if (dstX + dstW < 0 || dstX >= screen.GetWidth()) return;
	if (dstY + dstH < 0 || dstY >= screen.GetHeight()) return;

	// Draw the unclipped part of the tile.
	Pixel* dst = screen.GetBuffer() + dstX + dstY * screen.GetPitch();
	Pixel* src = tileSurface.GetBuffer() + srcX + srcY * tileSurface.GetPitch();

	for (int y = 0; y < dstH; ++y)
	{
		memcpy(dst, src, sizeof(Pixel) * dstW);
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
