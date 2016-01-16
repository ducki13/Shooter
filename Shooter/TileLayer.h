#ifndef _TileLayer_
#define _TileLayer_

#include "Level.h"
//#include "Layer.h"
#include "Vector2D.h"
#include <vector>

class TileLayer : public Layer		//holds data for tile layer
{
public:
	TileLayer(int tileSize, const std::vector<Tileset> &tilesets);

	virtual void update();
	virtual void render();

	void setTileIDs(const std::vector<std::vector<int>>& data);
	void setTileSize(int tileSize);

	Tileset getTilesetByID(int tileID);

private:
	int m_numColumns;
	int m_numRows;
	int m_tileSize;

	// Vector2D used when we start to scroll maps
	Vector2D m_position;
	Vector2D m_velocity;

	const std::vector<Tileset> &m_tilesets;

	std::vector<std::vector<int>> m_tileIDs;
};

#endif
