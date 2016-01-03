#ifndef __GameOverState__
#define __GameOverState__

#include "GameState.h"
#include "GameObject.h"

class GameOverState : public GameState
{
public:
    void update();
    void render();

    bool onEnter();
    bool onExit();

    std::string getStateID() const { return s_gameOverID; }

private:
    static void s_gameOverToMain();
    static void s_restartPlay();

    static const std::string s_gameOverID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* __GameOverState__ */


