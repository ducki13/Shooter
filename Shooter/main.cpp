#include "Game.h"

// our Game object
Game *g_game = 0;

int main(int argc, char *argv[])
{
    g_game = new Game();

    //g_game->init("Space shooter", 100, 100, 1024, 768, SDL_WINDOW_SHOWN); // FULL SCREEN
	
	g_game->init("Space shooter", 100, 100, 1024, 768, false); // FRee Window 

    while (g_game->running())
    {
        g_game->handleEvents();
        g_game->update();
        g_game->render();
    }
    g_game->clean();

    delete g_game;
    return 0;
}
