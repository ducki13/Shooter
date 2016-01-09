#pragma once

#pragma once
#include "SDLGameObject.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
// Enemy class
class Enemy : public SDLGameObject
{
public:
    Enemy();
    void load(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();
};

class EnemyCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Enemy();
    }
};
