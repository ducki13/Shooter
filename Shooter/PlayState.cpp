#include "PlayState.h"

#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"

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

    if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
        dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
    {
        Game::Instance()->getStateMachine()->changeState(new GameOverState());
    }
    
    pLevel->update();
}

void PlayState::render()
{
    pLevel->render();

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

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = leftA + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = topA + p1->getHeight();

    leftB = p2->getPosition().getX();
    rightB = leftB + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = topB + p2->getHeight();

    if (bottomA < topB) return false;
    if (bottomB < topA) return false;
    if (rightA < leftB) return false;
    if (leftA > rightB) return false;

    return true;
}
