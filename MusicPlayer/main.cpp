#include "SDL.h"
#include "SDL_rwops.h"
#include "SDL2_mixer/include/SDL_mixer.h"
#include "SDL_filesystem.h"

#include <iostream>
#include <queue>
#include <filesystem>
#include <vector>


#include "imgui.h"
#include "ImGui/backends/imgui_impl_sdl2.h"
#include "ImGui/backends/imgui_impl_sdlrenderer2.h"
#include "ImGui/misc/cpp/imgui_stdlib.h" //std::string users: Add misc/cpp/imgui_stdlib.* to easily use InputText with std::string.

using fsPath = std::filesystem::path;
void music_finished(void)
{
    /*indexSong++;
    Mix_FreeMusic(music);
    Mix_LoadMUS(songs[indexSong].c_str());
    Mix_PlayMusic(music, 1);*/
        
}
// habe n Songs, das nächste soll spielen, wenn das letzte geendet hat.

fsPath musicPath("/music");

static const std::string rain = "music/Rain.mp3";
static const std::string meer = "music/Meer.mp3";
Mix_Music* music;

std::vector <std::string> songs;
unsigned int indexSong = 0;



constexpr unsigned short WINwidth = 1280, WINheight = 720;

int main(int argc, char** argv) {  
    //path
    
    //SDL
    SDL_Window *window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    SDL_Rect Recti{ WINwidth / 2,WINheight / 2,50,50 };
    SDL_Rect backWards{ ((WINwidth / 2) - 70) ,WINheight / 2,50,50 };
    SDL_Rect forWards{ ((WINwidth / 2) + 70) ,WINheight / 2,50,50 };
    char* basePth = SDL_GetBasePath();
    std::cout << basePth << "\n";
  
  
    
    bool endIt = false;
    bool playing = false;
    
    int result = 0;
    int flags = MIX_INIT_MP3;

    //SDL Init
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO  ) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }
    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    //Audio and play
    songs.push_back(meer);
    songs.push_back(rain);
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    music = Mix_LoadMUS(songs[indexSong].c_str());
    if (Mix_PlayMusic(music, 1))
        playing = true;
    //Mix_HookMusicFinished(music_finished);
    
    //create Window and Renderer lol
    SDL_CreateWindowAndRenderer(WINwidth, WINheight, 0, &window, &renderer);

    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGui_ImplSDLRenderer2_Init(renderer);

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
                        if (playing) {
                            Mix_PauseMusic();
                            playing = false;
                            std::cout << SDL_GetAudioStatus() <<"\n";
                            std::cout << (double) Mix_MusicDuration(music) << "\n";

                        }
                        else {
                            Mix_ResumeMusic();
                            playing = true;
                            std::cout << SDL_GetAudioStatus() << "\n";
                        }
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
            if (playing == true)
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
        

    //free everything
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_free(basePth);
    SDL_Quit();
    return 0;
}