#pragma once
#include "Enemy.h"
#include "Game.h"
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
	TextureManager::Instance()->drawFrame(m_textureID,
		(int)m_position.getX(), (int)m_position.getY(), m_width,
		m_height, m_currentRow, m_currentFrame,
		TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
}

void Enemy::update()
{
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
{
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
	position = (rand() % 10000 + 500) + 5000;
}
