#include "TileLayer.h"
#include "Game.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) :
	m_tileSize(tileSize), m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
	m_numColumns = (TheGame::Instance()->getGameWidth() / m_tileSize);
	m_numRows = (TheGame::Instance()->getGameHeight() / m_tileSize);
}

void TileLayer::update()
{
	m_position += m_velocity;
	m_velocity.setX(5);
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data)
{
	m_tileIDs = data;
}

void TileLayer::setTileSize(int tileSize)
{
	m_tileSize = tileSize;
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID&&tileID < m_tilesets[i + 1].firstGridID)
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}
	}
	std::cout << "Did not find tileset. Returning empty tileset.\n";
	Tileset t;
	return t;
}

void TileLayer::render()
{
	int x, y, x2, y2 = 0;

	x = (int)(m_position.getX() / m_tileSize);//%1884;
	y = (int)(m_position.getX() / m_tileSize);//%1064;

	x2 = int(m_position.getX()) % m_tileSize;
	y2 = int(m_position.getY()) % m_tileSize;

	for (int i = 0; i < m_tileIDs.size(); ++i) //{//m_numRows; i++)
	{
		for (int j = 0; j < m_tileIDs[i].size(); ++j ) //{//m_numColumns+1; j++)
		{
			int id = m_tileIDs[i][(j + x)%58];
			//printf("i=%d j=%d x=%d id=%d j+x=%d (j + x)%58=%d \n", i, j, x, id, j + x, (j + x)%58);
			
			//int id = m_tileIDs[i][j + x];
			if (id == 0)
			{
				continue;
			}

			Tileset tileset = getTilesetByID(id);
			
			id--;
			//printf(">>>%d %d\n", (j * m_tileSize) - x2, (i * m_tileSize) - y2);
			TheTextureManager::Instance()->drawTile(tileset.name, 2, 2,
				(j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize,
				m_tileSize, (id - (tileset.firstGridID - 1)) /
				tileset.numColumns, (id - (tileset.firstGridID - 1)) %
				tileset.numColumns, TheGame::Instance()->getRenderer());
		}
	}
}

