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

class Asteroid : public Enemy {
public:
	Asteroid();
	void update();
private:
	int position;
};

class AsteroidCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Asteroid();
    }
};
