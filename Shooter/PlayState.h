#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"
#include "GameObject.h"
#include "LevelParser.h"
#include "Level.h"

class PlayState : public GameState
{
public:
    void update();
    void render();

    bool onEnter();
    bool onExit();

    std::string getStateID() const { return s_playID; }

private:
    static const std::string s_playID;

    std::vector<GameObject*> m_gameObjects;

	Level* pLevel;
};

#endif /* __PlayState__ */
