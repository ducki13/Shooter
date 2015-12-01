#pragma once

#pragma once
#include "SDLGameObject.h"
#include "GameObject.h"
// Enemy class
class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
};