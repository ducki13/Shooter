#pragma once
#include <SDL.h>
#include "Game.h"

#include <SDL_joystick.h>
#include "SDL_mixer.h"
#include "InputHandler.h"

const int InputHandler::m_joystickDeadZone;
InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() : m_keystates(0), m_mousePosition(new Vector2D(0, 0))
{
	// create button states for the mouse
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}

    m_bJoysticksInitialized = false;
}

void InputHandler::initializeJoysticks()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    int numJoysticks = SDL_NumJoysticks();
    if (numJoysticks > 0)
    {
        for (int i = 0; i < numJoysticks; i++)
        {
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            if (joy != NULL)
            {
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(
                    new Vector2D(0, 0), new Vector2D(0, 0)));

                std::vector<bool> buttons;
                for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
                {
                    buttons.push_back(false);
                }
                m_buttonStates.push_back(buttons);
            }
            else
            {
                std::cout << "Cannot open Joystick: "
                    << SDL_GetError() << std::endl;
            }
        }

        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialized = true;

        std::cout << "Initialized " << m_joysticks.size()
            << " joystick(s)" << std::endl;
    }
    else
    {
        m_bJoysticksInitialized = false;

        std::cout << "No joystick has been found" << std::endl;
    }
}

void InputHandler::clean()
{

}

void InputHandler::reset()
{
    m_mouseButtonStates[LEFT] = false;
    m_mouseButtonStates[RIGHT] = false;
    m_mouseButtonStates[MIDDLE] = false;
}

void InputHandler::update()
{

	//zbiorcze podsumowanie
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
        case SDL_JOYAXISMOTION:
            onJoystickAxisMove(event);
            break;
        case SDL_JOYBUTTONDOWN:
            onJoystickButtonDown(event);
            break;
        case SDL_JOYBUTTONUP:
            onJoystickButtonUp(event);
            break;
		default:
			break;
		}
	}
}


//keyboard
bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void InputHandler::onKeyDown()
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(0);
}

//mouse
void InputHandler::onMouseButtonDown(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}
bool InputHandler::getMouseButtonState(int buttonNumber) const
{
	return m_mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition() const
{
	return m_mousePosition;
}

void InputHandler::onMouseMove(SDL_Event &event)
{
	m_mousePosition->setX(event.motion.x);
	m_mousePosition->setY(event.motion.y);
}

int InputHandler::xvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0)
    {
        if (stick == 1)
        {
            return m_joystickValues[joy].first->getX();
        }
        else if (stick == 2)
        {
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0)
    {
        if (stick == 1)
        {
            return m_joystickValues[joy].first->getY();
        }
        else if (stick == 2)
        {
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
}

void InputHandler::onJoystickAxisMove(SDL_Event& event)
{
    int whichOne = event.jaxis.which;
    //std::cout << "Registered axis motion event from "
    //    << whichOne << " device" << std::endl;

    //int turn = (event.jaxis.value > m_joystickDeadZone) ? 1
    //    : (event.jaxis.value < -m_joystickDeadZone) ? -1 : 0;
    float velocity = (2.0f * event.jaxis.value) / m_joystickDeadZone;

    //if (event.jaxis.value > m_joystickDeadZone
    //    || event.jaxis.value < -m_joystickDeadZone)
    //{
    //    std::cout << "Value is " << event.jaxis.value << std::endl;
    //    std::cout << "Turn is " << turn << std::endl;
    //    std::cout << "Axis is " << (int) event.jaxis.axis << std::endl;
    //}

    switch (event.jaxis.axis)
    {
    case 0:
        m_joystickValues[whichOne].first->setX(velocity);
        break;
    case 1:
        m_joystickValues[whichOne].first->setY(velocity);
        break;
    case 2:
        m_joystickValues[whichOne].second->setX(velocity);
        break;
    case 4:
        m_joystickValues[whichOne].second->setY(velocity);
        break;
    }
}

void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
    int whichOne = event.jaxis.which;
    //std::cout << "Registered button no. " << (int) event.jbutton.button
    //    << " down event from " << whichOne << " device" << std::endl;

    m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
    int whichOne = event.jaxis.which;
    //std::cout << "Registered button no. " << (int) event.jbutton.button
    //    << " up event from " << whichOne << " device" << std::endl;

    m_buttonStates[whichOne][event.jbutton.button] = false;
}
