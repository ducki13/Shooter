#include "MenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for (GameObject* pGameObject : m_gameObjects)
    {
        pGameObject->update();
    }
}

void MenuState::render()
{
    for (GameObject* pGameObject : m_gameObjects)
    {
        pGameObject->draw();
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

    GameObject* button1 = new MenuButton(
        new LoaderParams(100, 100, 400, 100, "playbutton"));

    GameObject* button2 = new MenuButton(
        new LoaderParams(100, 300, 400, 100, "exitbutton"));

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
