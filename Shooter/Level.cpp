#include "Level.h"

void Level::render()	//updates all layers
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->render();
	}
}

void Level::update()	//updates all layers
{
	for (int i = 0; i < m_layers.size(); i++)
	{
		m_layers[i]->update();
	}
}