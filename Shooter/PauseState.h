#ifndef __PauseState__
#define __PauseState__

#include "GameState.h"
#include "GameObject.h"

class PauseState : public GameState
{
public:
    void update();
    void render();

    bool onEnter();
    bool onExit();

    std::string getStateID() const { return s_pauseID; }

private:
    static void s_pauseToMain();
    static void s_resumePlay();

    static const std::string s_pauseID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* __PauseState__ */
