#include "SDL2/include/SDL.h"
#include "Player.h"
#include "SDLC.h"

#include <iostream>
#include <filesystem>
#include <vector>


#include "imgui.h"
#include "ImGui/backends/imgui_impl_sdl2.h"
#include "ImGui/backends/imgui_impl_sdlrenderer2.h"
#include "ImGui/misc/cpp/imgui_stdlib.h" //std::string users: Add misc/cpp/imgui_stdlib.* to easily use InputText with std::string.



std::string musicPath = "music/";
static const std::string rain = musicPath + "Rain.mp3";
static const std::string meer = musicPath + "Meer.mp3";

constexpr unsigned short WINwidth = 1280, WINheight = 720;

int main(int argc, char** argv) {  
    //SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    SDL_Rect Recti{ WINwidth / 2,WINheight / 2,50,50 };
    SDL_Rect backWards{ ((WINwidth / 2) - 70) ,WINheight / 2,50,50 };
    SDL_Rect forWards{ ((WINwidth / 2) + 70) ,WINheight / 2,50,50 };
    bool endIt = false;

    //SDL Init
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO  ) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }
    
 
    Player player;

    player.loadMusic(meer.c_str());
    player.loadMusic(rain.c_str());
    player.playMusic(0);
    
    SDL_CreateWindowAndRenderer(WINwidth, WINheight, 0, &window, &renderer); 

    //Mix_HookMusicFinished(music_finished);
   
    while (!endIt) {
     
            //poll event
            while (SDL_PollEvent(&event)) {

                switch (event.type) {

                case SDL_QUIT:
                    endIt = true;
                    break;
                case SDL_KEYDOWN:
                    if(SDLK_SPACE == event.key.keysym.sym)
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



            //rendering
            SDL_Delay(1000/60); //calculates to 60 fps
            SDL_SetRenderDrawColor(renderer, 69, 10, 69, 255);
            SDL_RenderClear(renderer);
            if (Mix_PausedMusic() == 1)
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderFillRect(renderer, &Recti);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &Recti);
            }

            SDL_SetRenderDrawColor(renderer, 169, 0, 255, 255);
            SDL_RenderFillRect(renderer, &backWards);


            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(renderer, &forWards);

            SDL_RenderPresent(renderer);
               
     }
        


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}