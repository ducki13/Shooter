#pragma once
#include "Player.h"
#include "LoaderParams.h"
#include <SDL.h>
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "Vector2D.h"
#include "TextureManager.h"
#include "Game.h"
#include "SoundManager.h"
#include "BulletHandler.h"

Player::Player() : SDLGameObject()
{
}

void Player::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
}

void Player::draw()
{
    SDL_RendererFlip flip;

    flip = SDL_FLIP_NONE;

    TextureManager::Instance()->drawFrame(m_textureID,
        m_position.getX(), m_position.getY(),
        m_width, m_height, m_currentRow, m_currentFrame,
        Game::Instance()->getRenderer(), flip);
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
	handleInput(); // add our function
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
	SDLGameObject::update();
}

void Player::clean()
{
}


// mouse and kayboard Controls
void Player::handleInput()
{
	//myszka test inputu
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(1);
	}

	//keyboard
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-2);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(2);
	}


	//mouse position, animation go after the coursor
	//*********************************************************************************** jeœli chcesz, ¿eby input w postaci klawiszy dzia³a³ to zkomentuje 2 poni¿sze wiersze kodu
	//Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	//m_velocity = (*vec - m_position) / 100;


    if (TheInputHandler::Instance()->joysticksInitialized())
    {
        if (TheInputHandler::Instance()->xvalue(0, 1) != 0)
        {
            m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 1));
        }
        if (TheInputHandler::Instance()->yvalue(0, 1) != 0)
        {
            m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 1));
        }
        if (TheInputHandler::Instance()->xvalue(0, 2) != 0)
        {
            m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 2));
        }
        if (TheInputHandler::Instance()->yvalue(0, 2) != 0)
        {
            m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 2));
        }
        if (TheInputHandler::Instance()->getButtonState(0, 3))
        {
            m_velocity.setX(1);
        }
    }

    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) ||
        (TheInputHandler::Instance()->joysticksInitialized() && TheInputHandler::Instance()->getButtonState(0, 0)))
    {
        SoundManager::Instance()->playSound("shoot", 0);
        BulletHandler::Instance()->addPlayerBullet(
            m_position.getX() + 10, m_position.getY() + 10,
            32, 32, "bullet1", 1, Vector2D(5, 0));
    }
}
