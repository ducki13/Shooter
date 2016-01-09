#ifndef __MenuButton__
#define __MenuButton__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class MenuButton : public SDLGameObject
{
public:
    MenuButton();
    void load(const LoaderParams* pParams);

    void draw();
    void update();
    void clean();
private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void(*m_callback)();
    bool m_bReleased;
};

class MenuButtonCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new MenuButton();
    }
};

#endif /* __MenuButton__ */
