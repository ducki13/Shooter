#ifndef __ObjectLayer__
#define __ObjectLayer__

#include <vector>

#include "Layer.h"
#include "GameObject.h"
#include "SDLGameObject.h"
#include "PlayState.h"
#include "GameOverState.h"
#include "Game.h"

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
    
    bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
};

#endif /* __ObjectLayer__ */
