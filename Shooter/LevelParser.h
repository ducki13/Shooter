#ifndef _LevelParser_
#define _LevelParser_

#include "tinyxml.h"
#include "Level.h"
#include <vector>

class LevelParser	//parses .tmx files and creates levels from them
{
public:

	Level* parseLevel(const char* levelFile);

private:

	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);

	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets);

	int m_tileSize;
	int m_width;
	int m_height;
};

#endif
