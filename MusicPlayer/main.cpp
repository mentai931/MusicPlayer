#include "SDL2/include/SDL.h"
#include "Player.h"
#include "SDLC.h"

#include <iostream>
#include <filesystem>
#include <vector>

Player player;

void songFinished()
{
    
    std::cout << player.songIndex << " before ++\n";
    Mix_Music* tmp = player.songs[player.songIndex];
    Mix_FreeMusic(tmp);
    tmp = NULL;
    player.songIndex++;
    std::cout << player.songIndex << " after ++\n";
    if (player.songIndex < player.songs.size())
    {
        if (Mix_PlayingMusic() == 0) 
        {
            Mix_PlayMusic(player.songs[player.songIndex], 0); 
            std::cout << player.songs.size() << std::endl;
        }
    }
    else
    {
        std::cout << "Keine Songs mehr auf der Liste\n";
        //TODO Bug behandeln
    }
    

}



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
    
 
    
    player.loadMusic(meer.c_str());
    player.loadMusic(rain.c_str());
    player.playMusic(0);
    Mix_HookMusicFinished(songFinished);
    SDL_CreateWindowAndRenderer(WINwidth, WINheight, 0, &window, &renderer); 

    Mix_HookMusicFinished(songFinished);
   
    while (!endIt) {
     
            //poll event
            while (SDL_PollEvent(&event)) {

                switch (event.type) {

                case SDL_QUIT:
                    endIt = true;
                    break;
                case SDL_KEYDOWN:
                    
                    if (SDLK_q == event.key.keysym.sym)
                    {
                        endIt = true;
                    }
                    if (SDLK_j == event.key.keysym.sym)
                    {
                        Mix_RewindMusic();
                    }
                    if (SDLK_k == event.key.keysym.sym)
                    {
                        player.togglePlay();
                    }
                    if (SDLK_l == event.key.keysym.sym)
                    {
                        Mix_HaltMusic();
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