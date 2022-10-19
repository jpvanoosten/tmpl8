#include "TileMap.h"
#include <algorithm>

using namespace Tmpl8;

int TileMap::NUM_SOMETHING = 5;

TileMap::TileMap(const char* file)
	: tileSurface(file)
{}

const Tile* TileMap::GetTile(int x, int y) const
{
	if (x < 0 || x >= width) return nullptr;
	if (y < 0 || y >= tiles.size() / width) return nullptr;

	int i = x + y * width;
	return &(tiles[i]);
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
	if (tiles.empty()) return false;

	int tileWidth = tiles[0].width;
	int tileHeight = tiles[0].height;

	Tmpl8::vec2 localPoint = p - position;

	int tileX = static_cast<int>(localPoint.x / tileWidth);
	int tileY = static_cast<int>(localPoint.y / tileHeight);

	const Tile* tile = GetTile(tileX, tileY);
	if (tile)
	{
		return tile->isBlocking;
	}

	return false;
}

bool TileMap::Collides(const Bounds& bounds) const
{
	if (tiles.empty()) return false;

	int tileWidth = tiles[0].width;
	int tileHeight = tiles[0].height;

	vec2 min = bounds.min;
	vec2 max = bounds.max;

	vec2 p = min;
	while (p.y < max.y + tileHeight)
	{
		p.x = min.x;
		while (p.x < max.x + tileWidth)
		{
			if (Collides(vec2{std::min(p.x, max.x), std::min(p.y, max.y)})) return true;
			p.x += tileWidth;
		}
		p.y += tileHeight;
	}

	return false;
}


void TileMap::DrawTile(Tmpl8::Surface& screen, const Tile& tile, int tileX, int tileY)
{
	int dstW = tile.width;
	int dstH = tile.height;
	int dstX = static_cast<int>(position.x + (tileX * tile.width));
	int dstY = static_cast<int>(position.y + (tileY * tile.height));

	// Check if the entire tile is clipped.
	if (dstX + dstW < 0 || dstX >= screen.GetWidth()) return;
	if (dstY + dstH < 0 || dstY >= screen.GetHeight()) return;

	// Compute the amount to clip.
	int clipLeft = std::min(0, dstX);
	int clipTop = std::min(0, dstY);		
	int clipRight = std::max(0, dstX + dstW - screen.GetWidth());
	int clipBottom = std::max(0, dstY + dstH - screen.GetHeight());

	// Adjust the destination rectangles according to the clipping.
	dstX -= clipLeft;
	dstY -= clipTop;
	dstW -= clipRight - clipLeft;
	dstH -= clipBottom - clipTop;

	int srcX = tile.x * (tile.width + 1) + 1;
	int srcY = tile.y * (tile.height + 1) + 1;
	// Account for clipping.
	srcX -= clipLeft;
	srcY -= clipTop;

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

void TileMap::Draw(Tmpl8::Surface& screen, const Tmpl8::vec2& wp)
{
	auto curPos = position;
	position += wp;
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
	position = curPos;
}
