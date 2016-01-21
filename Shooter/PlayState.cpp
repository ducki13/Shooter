#include "PlayState.h"

#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "BulletHandler.h"

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
    
    pLevel->update();
    BulletHandler::Instance()->updateBullets();
}

void PlayState::render()
{
    pLevel->render();
    BulletHandler::Instance()->drawBullets();

    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PlayState::onEnter()
{
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/space_tilemap.tmx");

    // Parse the states file
    StateParser stateParser;
    stateParser.parseState("assets/states-config.xml", s_playID, &m_gameObjects, &m_textureIDList);
	
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

    // Clear the texture manager
    for (std::string textureID : m_textureIDList)
    {
        TextureManager::Instance()->clearFromTextureMap(textureID);
    }

    std::cout << "Exiting PlayState" << std::endl;
    return true;
}
