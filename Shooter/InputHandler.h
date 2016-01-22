#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
    static const int m_joystickDeadZone = 10000;

	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}

    void initializeJoysticks();
    bool joysticksInitialized() { return m_bJoysticksInitialized; }

    void reset();

	void update();
	void clean();

    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

    bool getButtonState(int joy, int buttonNumber)
    {
        return m_buttonStates[joy][buttonNumber];
    }

	//keyboard
	//Uint8* m_keystate;
	const Uint8* m_keystates;

	bool isKeyDown(SDL_Scancode key);

	// zbiorcze inputy w zaleznosci od kontrolera
	// private functions to handle different event types

	// handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// mouse events
	bool getMouseButtonState(int buttonNumber) const;
	Vector2D* getMousePosition() const;

    /* Joystick events */
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);

private:
	InputHandler();
	~InputHandler() {}
	static InputHandler* s_pInstance;

	// mouse specific
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;

    // joystick specific
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoysticksInitialized;

    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
};
typedef InputHandler TheInputHandler;
