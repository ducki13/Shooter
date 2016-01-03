#include "PauseState.h"

#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "MenuState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void PauseState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool PauseState::onEnter()
{
    TextureManager* pTM = TextureManager::Instance();
    SDL_Renderer* pR = Game::Instance()->getRenderer();

    if (!pTM->load("assets/resume.png", "resumebutton", pR))
    {
        return false;
    }
    if (!pTM->load("assets/main.png", "mainbutton", pR))
    {
        return false;
    }

    GameObject* button1 = new MenuButton(
        new LoaderParams(200, 100, 200, 80, "mainbutton"),
        s_pauseToMain);

    GameObject* button2 = new MenuButton(
        new LoaderParams(200, 300, 200, 80, "resumebutton"),
        s_resumePlay);

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "Entering PauseState" << std::endl;
    return true;
}

bool PauseState::onExit()
{
    TextureManager* pTM = TextureManager::Instance();

    for (GameObject *pGameObject : m_gameObjects)
    {
        pGameObject->clean();
    }
    m_gameObjects.clear();

    pTM->clearFromTextureMap("resumebutton");
    pTM->clearFromTextureMap("mainbutton");

    // reset the mouse button states to false
    InputHandler::Instance()->reset();

    std::cout << "Exiting PauseState" << std::endl;
    return true;
}

void PauseState::s_pauseToMain()
{
    Game::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay()
{
    Game::Instance()->getStateMachine()->popState();
}
