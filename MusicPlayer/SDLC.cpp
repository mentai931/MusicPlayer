#include "SDLC.h"
#include "stdio.h"

SDLC::SDLC()
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }
    SDL_CreateWindowAndRenderer(WINwidth, WINheight, 0, &window, &renderer);
    endIt = false;

}

SDLC::~SDLC()
{
    endIt = true;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*void SDLC::input()
{
    while (SDL_PollEvent(&event)) {

        switch (event.type) {

        case SDL_QUIT:
            endIt = true;
            break;
        case SDL_KEYDOWN:
            if (SDLK_SPACE == event.key.keysym.sym)
            {
                player.togglePlay();
            }
            if (SDLK_j == event.key.keysym.sym)
            {
                Mix_RewindMusic();
            }
            if (SDLK_q == event.key.keysym.sym)
            {
                endIt = true;
            }
            break;
        default:
            break;
        }

    }
}*/