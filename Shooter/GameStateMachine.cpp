#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* pState)
{
    if (!m_gameStates.empty())
    {
        if (m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return;
        }
        popState();
    }
    pushState(pState);
}

void GameStateMachine::popState()
{
    if (!m_gameStates.empty())
    {
        if (m_gameStates.back()->onExit())
        {
            //delete m_gameStates.back(); // crashes with callbacks
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::update()
{
    if (!m_gameStates.empty())
    {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render()
{
    if (!m_gameStates.empty())
    {
        m_gameStates.back()->render();
    }
}
