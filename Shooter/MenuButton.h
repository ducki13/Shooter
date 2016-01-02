#ifndef __MenuButton__
#define __MenuButton__

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
    MenuButton(const LoaderParams* pParams);

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
};

#endif /* __MenuButton__ */
