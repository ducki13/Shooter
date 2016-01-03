#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic(const LoaderParams* pParams, int animSpeed);

    void draw();
    void update();
    void clean();

private:
    int m_animSpeed;
};

#endif /* __AnimatedGraphic__ */
