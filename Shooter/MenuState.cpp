#include "MenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
    }
}

void MenuState::render()
{
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }
}

bool MenuState::onEnter()
{
    TextureManager* pTM = TextureManager::Instance();
    SDL_Renderer* pR = Game::Instance()->getRenderer();

    if (!pTM->load("assets/button.png", "playbutton", pR))
    {
        return false;
    }
    if (!pTM->load("assets/exit.png", "exitbutton", pR))
    {
        return false;
    }

    GameObject* button1 = new MenuButton();
    button1->load(new LoaderParams(200, 150, 400, 100, "playbutton", s_menuToPlay));

    GameObject* button2 = new MenuButton();
    button2->load(new LoaderParams(200, 350, 400, 100, "exitbutton", s_exitFromMenu));

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "Entering MenuState" << std::endl;
    return true;
}

bool MenuState::onExit()
{
    TextureManager* pTM = TextureManager::Instance();

    for (GameObject *pGameObject : m_gameObjects)
    {
        pGameObject->clean();
    }
    m_gameObjects.clear();

    pTM->clearFromTextureMap("playbutton");
    pTM->clearFromTextureMap("exitbutton");

    std::cout << "Exiting MenuState" << std::endl;
    return true;
}

void MenuState::s_menuToPlay()
{
    Game::Instance()->getStateMachine()
        ->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
    Game::Instance()->quit();
}
