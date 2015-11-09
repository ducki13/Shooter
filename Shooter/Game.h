#include "SDL.h"

#ifndef __Game__
#define __Game__

class Game
{
public:
    Game() {}
    ~Game() {}

    bool init(const char* title, int xpos, int ypos,
        int width, int height, int flags);
    void render();
    void update();
    void handleEvents();
    void clean();

    // a function to access the private running variable
    bool running() { return m_bRunning; }

private:
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;

    bool m_bRunning;
};

#endif /* defined(__Game__) */
