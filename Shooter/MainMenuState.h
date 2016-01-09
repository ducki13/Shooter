#ifndef __MainMenuState__
#define __MainMenuState__

#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState
{
public:
    void update();
    void render();

    bool onEnter();
    bool onExit();

    std::string getStateID() const { return s_menuID; }
private:
    void setCallbacks(const std::vector<Callback>& callbacks);

    static void s_menuToPlay();
    static void s_exitFromMenu();

    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* __MainMenuState__ */
