#pragma once
#include "Enemy.h"
#include "LoaderParams.h"
#include <SDL.h>
#include "SDLGameObject.h"
#include <stdlib.h>
#include <time.h>

Enemy::Enemy() : SDLGameObject()
{

}

void Enemy::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);

    m_velocity.setX(0.001);
    m_velocity.setY(2);
}

void Enemy::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Enemy::update()
{	printf("Enemy:%d\n", SDL_GetTicks());
    m_currentFrame = (SDL_GetTicks() / 100) % 5;

    if (m_position.getY() < 0)
    {
        m_velocity.setY(2);
    }
    else if (m_position.getY() > 400)
    {
        m_velocity.setY(-2);
    }

    SDLGameObject::update();
}

void Enemy::clean()
{
}

void Asteroid::update()
{	printf("Asteroid:%d pos=%d\n", SDL_GetTicks(), position);
	if(SDL_GetTicks() < position) return;	
	m_currentFrame = (SDL_GetTicks() / 100) % 5;

	if (m_position.getY() < 0)
	{
		m_velocity.setY(2);
	}
	else if (m_position.getY() > 400)
	{
		m_velocity.setY(-2);
	}
	m_velocity.setX(-1);
	SDLGameObject::update();
}

Asteroid::Asteroid() {
	srand(time(NULL));
	position = (rand() % 1000 + 500) + 100;
	printf("pos=%d\n", position);
}
