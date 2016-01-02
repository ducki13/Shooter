#include "MenuButton.h"

#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams)
    : SDLGameObject(pParams)
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
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}
