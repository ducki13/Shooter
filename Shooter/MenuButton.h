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

    void setCallback(void(*callback)()) { m_callback = callback; }
    int getCallBackID() { return m_callbackID; }
private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void(*m_callback)();
    int m_callbackID;
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
