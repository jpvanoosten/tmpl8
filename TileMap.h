#pragma once

#include "surface.h"
#include <string>
#include <vector>

struct Tile
{
	bool isBlocking = false;
};

class TileMap {
public:

	/// <summary>
	/// Create a tile map with initial width and height.
	/// </summary>
	/// <param name="file">The file path of the tile map.</param>
	/// <param name="width">Number of tiles in the X axis.</param>
	/// <param name="height">Number of tiles in the Y axis.</param>
	TileMap(const char* file, int width, int height);

	const Tile& GetTile(int x, int y) const;
	void SetTile(int x, int y, const Tile& tile);
	void SetTiles(const std::vector<Tile>& tiles);

	const Tile& operator()(int x, int y) const
	{
		return GetTile(x, y);
	}

	void Draw(Tmpl8::Surface& screen, int xoffset = 0, int yoffset = 0);

protected:
	

private:
	Tmpl8::Surface tileSurface;
	int width;
	int height;
	std::vector<Tile> tiles;
};