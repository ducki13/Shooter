#include "PlayState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    // nothing for now
}

void PlayState::render()
{
	pLevel->render();
}

bool PlayState::onEnter()
{
    LevelParser levelParser;
	pLevel = levelParser.parseLevel("space_tile_map.tmx");
    std::cout << "Entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit()
{
    std::cout << "Exiting PlayState" << std::endl;
    return true;
}
