#include "PlayState.h"

#include "TextureManager.h"
#include "Game.h"
#include "Player.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void PlayState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter()
{
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("space_tile_map.tmx");

    if (!TextureManager::Instance()->load(
        "assets/helicopter.png", "helicopter",
        Game::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* player = new Player(
        new LoaderParams(100, 100, 128, 50, "helicopter"));
    m_gameObjects.push_back(player);

    std::cout << "Entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();

    TextureManager::Instance()->clearFromTextureMap("helicopter");

    std::cout << "Exiting PlayState" << std::endl;
    return true;
}
