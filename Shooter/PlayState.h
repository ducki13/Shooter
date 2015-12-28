#include "LevelParser.h"
#include "Level.h"
#include <iostream>

class PlayState {
public:
	
	bool onEnter();
	void render();

private:

	Level* pLevel; //TODO: check type of the variable
};