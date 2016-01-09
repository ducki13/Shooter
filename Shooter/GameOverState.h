#ifndef __GameOverState__
#define __GameOverState__

#include "MenuState.h"
#include "GameObject.h"

class GameOverState : public MenuState
{
public:
    void update();
    void render();

    bool onEnter();
    bool onExit();

    std::string getStateID() const { return s_gameOverID; }

private:
    void setCallbacks(const std::vector<Callback>& callbacks);

    static void s_gameOverToMain();
    static void s_restartPlay();

    static const std::string s_gameOverID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* __GameOverState__ */


