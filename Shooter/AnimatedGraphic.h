#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();
    void load(const LoaderParams* pParams);

    void draw();
    void update();
    void clean();

private:
    int m_animSpeed;
};

class AnimatedGraphicCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};

#endif /* __AnimatedGraphic__ */
