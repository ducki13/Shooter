#include "MenuButton.h"

#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams, void(*callback)())
    : SDLGameObject(pParams), m_callback(callback), m_bReleased(true)
{
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    InputHandler* pIH = InputHandler::Instance();
    Vector2D* pMousePos = pIH->getMousePosition();

    if (pMousePos->getX() >= m_position.getX() &&
        pMousePos->getX() <= m_position.getX() + m_width &&
        pMousePos->getY() >= m_position.getY() &&
        pMousePos->getY() <= m_position.getY() + m_height)
    {
        m_currentFrame = MOUSE_OVER;

        if (pIH->getMouseButtonState(LEFT))
        {
            m_currentFrame = CLICKED;
            if (m_bReleased)
            {
                m_callback();
                m_bReleased = false;
            }
        }
        else
        {
            m_bReleased = true;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
        m_bReleased = true;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}
