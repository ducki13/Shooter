#include "PlayState.h"


bool PlayState::onEnter()
{
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("assets/map1.tmx");
	std::cout << "entering PlayState\n";
	return true;
}

void PlayState::render()
{
	pLevel->render();
}