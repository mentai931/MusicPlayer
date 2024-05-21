#include "SDL.h"
#include "SDL2_mixer/include/SDL_mixer.h"
#include <iostream>
static const char* MY_COOL_MP3 = "Rain.mp3";

int main(int argc, char** argv) {  
    SDL_Window *window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    
    bool isRunning = true;
    bool playing = false;
    int result = 0;
    int flags = MIX_INIT_MP3;

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO  ) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }

    
    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }


    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music* music = Mix_LoadMUS(MY_COOL_MP3);
    if (Mix_PlayMusic(music, 1))
        playing = true;
                   
    SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);
    while (1) {
     

            while (SDL_PollEvent(&event)) {

                
                switch (event.type) {
                case SDL_KEYDOWN:
                    std::cout << "Key press detected amk \n";
                    if (playing) {
                        Mix_PauseMusic();
                        playing = false;
                    }
                    else {
                        Mix_ResumeMusic();
                        playing = true;
                    }
                        
                    break;

                case SDL_KEYUP:
                    std::cout << "Key press not detected \n";
                    

                    break;

                default:
                    break;
                }
            }
            SDL_Delay(1000);
     }
        



    /*while (!SDL_QuitRequested()) {
        SDL_Delay(250);

    }*/
    


    Mix_FreeMusic(music);
    SDL_Quit();
    return 0;
}