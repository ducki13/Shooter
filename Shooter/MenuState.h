#ifndef __MenuState__
#define __MenuState__

#include "GameState.h"

class MenuState : public GameState
{
public:
    void update();
    void render();

    bool onEnter();
    bool onExit();

    std::string getStateID() const { return s_menuID; }
private:
    static const std::string s_menuID;
};

#endif /* __MenuState__ */
