#pragma once
#include "Enemy.h"
#include "LoaderParams.h"
#include <SDL.h>
#include "SDLGameObject.h"


Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Enemy::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

//version with Vector 2D
void Enemy::update()
{
	m_position.setX(m_position.getX() + 1);
	m_position.setY(m_position.getY() + 1);
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}
//version with Vector 2D END

void Enemy::clean()
{
}