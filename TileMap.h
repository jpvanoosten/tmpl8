#pragma once

#include "surface.h"
#include <string>
#include <vector>

struct Tile
{
	// Is this a blocking tile?
	bool isBlocking = false;
	// The x pixels in the tilemap.
	int x;
	// The y pixels in the tilemap.
	int y;
	// The with of the tile in pixels.
	int width;
	// The height of the tile in pixels.
	int height;
};

struct int2
{
	int x;
	int y;
	
	int2(int x, int y)
		: x(x)
		, y(y)
	{}

	int2(float x, float y)
		: x(static_cast<int>(x))
		, y(static_cast<int>(y))
	{}
};

class TileMap 
{
public:

	/// <summary>
	/// Create a tile map with initial width and height.
	/// </summary>
	/// <param name="file">The file path of the tile map.</param>
	/// <param name="width">Number of tiles in the X axis.</param>
	/// <param name="height">Number of tiles in the Y axis.</param>
	TileMap(const char* file);

	const Tile& GetTile(int x, int y) const;
	void SetTile(int x, int y, const Tile& tile);

	/// <summary>
	/// Set the tiles of the tile map.
	/// </summary>
	/// <param name="tiles">The tilemap.</param>
	/// <param name="width">The number of tiles in the width of the tilemap.</param>
	void SetTiles(const std::vector<Tile>& tiles, int width);

	int2 GetSizeInPixels() const
	{
		int height = static_cast<int>(tiles.size()) / width;
		return { width * tiles[0].width, height * tiles[0].height };
	}

	void SetOffset(const int2& offset)
	{
		this->offset = offset;
	}

	const int2& GetOffset() const
	{
		return offset;
	}
	
	const Tile& operator()(int x, int y) const
	{
		return GetTile(x, y);
	}

	void Draw(Tmpl8::Surface& screen);

protected:
	

private:
	void DrawTile(Tmpl8::Surface& screen, const Tile& tile, int tileX, int tileY);

	Tmpl8::Surface tileSurface;
	std::vector<Tile> tiles;
	
	// Number of tiles in the width of the map.
	int width;
	int2 offset = { 0, 0 };
};