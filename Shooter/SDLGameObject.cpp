#pragma once
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

//version with Vector2D wersja z updatem velocity w konstruktorze
SDLGameObject::SDLGameObject(const LoaderParams* pParams) :GameObject(pParams), m_position(pParams->getX(), pParams ->getY()), m_velocity(0, 0), m_acceleration(0, 0)
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
}
//version with Vector2D END

//version with Vector 2D
void SDLGameObject::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID,
		(int)m_position.getX(), (int)m_position.getY(), m_width,
		m_height, m_currentRow, m_currentFrame,
		TheGame::Instance()->getRenderer());
}
//version with Vector 2D END

void SDLGameObject::update()
{
	m_position += m_velocity; //version after updatink velocity 2D vector in SDLGAMEObject class
	m_velocity += m_acceleration; //version after updatink aceleration 2D vector in SDLGAMEObject class
								  //akceleracja dodaje wartosc do predkosci, ktora odnosi sie do pozycja ktora jest odzwierciedlona w kodzie SDLGameObject::draw
}

void SDLGameObject::clean()
{
}
