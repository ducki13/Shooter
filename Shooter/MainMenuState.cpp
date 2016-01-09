#include "MainMenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MainMenuState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MainMenuState::onEnter()
{
    // Parse the states file
    StateParser stateParser;
    stateParser.parseState("assets/states-config.xml", s_menuID, &m_gameObjects, &m_textureIDList);

    m_callbacks.push_back(NULL); // callBackID starts from one
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);

    std::cout << "Entering MenuState" << std::endl;
    return true;
}

bool MainMenuState::onExit()
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

    std::cout << "Exiting MenuState" << std::endl;
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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

void MainMenuState::s_menuToPlay()
{
    Game::Instance()->getStateMachine()
        ->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    Game::Instance()->quit();
}
