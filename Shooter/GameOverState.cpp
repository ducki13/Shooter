#include "GameOverState.h"

#include "TextureManager.h"
#include "Game.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"

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
    TextureManager* pTM = TextureManager::Instance();
    SDL_Renderer* pR = Game::Instance()->getRenderer();

    if (!pTM->load("assets/gameover.png", "gameovertext", pR))
    {
        return false;
    }

    if (!pTM->load("assets/main.png", "mainbutton", pR))
    {
        return false;
    }

    if (!pTM->load("assets/restart.png", "restartbutton", pR))
    {
        return false;
    }

    GameObject* gameOverText = new AnimatedGraphic();
    gameOverText->load(new LoaderParams(200, 100, 190, 30, "gameovertext", 0, 2));

    GameObject* button1 = new MenuButton();
    button1->load(new LoaderParams(200, 200, 200, 80, "mainbutton", s_gameOverToMain));

    GameObject* button2 = new MenuButton();
    button2->load(new LoaderParams(200, 300, 200, 80, "restartbutton", s_restartPlay));

    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "Entering GameOverState" << std::endl;
    return true;
}

bool GameOverState::onExit()
{
    TextureManager* pTM = TextureManager::Instance();

    for (GameObject *pGameObject : m_gameObjects)
    {
        pGameObject->clean();
    }
    m_gameObjects.clear();

    pTM->clearFromTextureMap("gameovertext");
    pTM->clearFromTextureMap("mainbutton");
    pTM->clearFromTextureMap("restartbutton");

    // reset the mouse button states to false
    InputHandler::Instance()->reset();

    std::cout << "Exiting GameOverState" << std::endl;
    return true;
}

void GameOverState::s_gameOverToMain()
{
    Game::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay()
{
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}
