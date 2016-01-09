#ifndef __PauseState__
#define __PauseState__

#include "MenuState.h"
#include "GameObject.h"

class PauseState : public MenuState
{
public:
    void update();
    void render();

    bool onEnter();
    bool onExit();

    std::string getStateID() const { return s_pauseID; }

private:
    void setCallbacks(const std::vector<Callback>& callbacks);

    static void s_pauseToMain();
    static void s_resumePlay();

    static const std::string s_pauseID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* __PauseState__ */
