#pragma once
#include "Layer.h"

struct Tileset	//contains info about tilestes
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

class Level		//stores, draws, updates layers
{
public:
	void update();
	void render();

	std::vector<Tileset>* getTilesets()
	{
		return &m_tilesets;
	}

	std::vector<Layer*>* getLayers()
	{
		return &m_layers;
	}

	~Level() {}

private:
	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;

	friend class LevelParser;

	Level();	//LevelParser is allowed to create Level objects
};