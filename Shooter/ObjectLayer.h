#ifndef __ObjectLayer__
#define __ObjectLayer__

#include <vector>

#include "Layer.h"
#include "GameObject.h"

class ObjectLayer : public Layer
{
public:
    void update();
    void render();

    std::vector<GameObject*>* getGameObjects()
    {
        return &m_gameObjects;
    }

private:
    std::vector<GameObject*> m_gameObjects;
};

#endif /* __ObjectLayer__ */
