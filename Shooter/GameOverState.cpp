#include "GameOverState.h"

#include "TextureManager.h"
#include "Game.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void GameOverState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool GameOverState::onEnter()
{
    // Parse the states file
    StateParser stateParser;
    stateParser.parseState("assets/states-config.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(NULL);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    std::cout << "Entering GameOverState" << std::endl;
    return true;
}

bool GameOverState::onExit()
{
    for (GameObject *pGameObject : m_gameObjects)
    {
        pGameObject->clean();
    }
    m_gameObjects.clear();

    // Clear the texture manager
    for (std::string textureID : m_textureIDList)
    {
        TextureManager::Instance()->clearFromTextureMap(textureID);
    }

    // reset the mouse button states to false
    InputHandler::Instance()->reset();

    std::cout << "Exiting GameOverState" << std::endl;
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
    // Go through the game objects
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        // If they are of type MenuButton, then assign a callback
        // based on the id passed in from the file
        if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton *pButton =
                dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallBackID()]);
        }
    }
}

void GameOverState::s_gameOverToMain()
{
    Game::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}
