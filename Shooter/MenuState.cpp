#include "MenuState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    // nothing for now
}

void MenuState::render()
{
    // nothing for now
}

bool MenuState::onEnter()
{
    std::cout << "Entering MenuState" << std::endl;
    return true;
}

bool MenuState::onExit()
{
    std::cout << "Exiting MenuState" << std::endl;
    return true;
}
