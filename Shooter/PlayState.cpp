#include "PlayState.h"

#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "PauseState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Game::Instance()->getStateMachine()->pushState(new PauseState());
    }

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
    pLevel = levelParser.parseLevel("assets/space_tile_map.tmx");

    if (!TextureManager::Instance()->load(
        "assets/helicopter.png", "helicopter",
        Game::Instance()->getRenderer()))
    {
        return false;
    }

    if (!TextureManager::Instance()->load(
        "assets/helicopter2.png", "helicopter2",
        Game::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* player = new Player(
        new LoaderParams(100, 100, 128, 55, "helicopter"));

    GameObject* enemy = new Enemy(
        new LoaderParams(500, 100, 128, 55, "helicopter2"));

    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy);

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
