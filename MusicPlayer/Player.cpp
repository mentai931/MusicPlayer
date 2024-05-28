#include "Player.h"
#include "SDL2/include/SDL.h"
bool Player::initMixer()
{
	Mix_Init(MIX_INIT_MP3);
	//SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_Mixer couldnt init. Err: %s\n", Mix_GetError());
		return false;
	}
	//musicPath = "music/";
	return true;
	
}

int Player::loadMusic(const char* filename)
{
	Mix_Music* m = NULL;
	m = Mix_LoadMUS(filename);
	if (m == NULL) {
		printf("Failed to load music. SDL_Mixer error: %s\n", Mix_GetError());
		return -1;
	}
	songs.push_back(m);
	return songs.size() - 1;
}

bool Player::playMusic(int index)
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(songs[index], 0);
	}
	return 0;
}

void Player::quitMixer()
{
	Mix_CloseAudio(); 
	for(auto &song : songs)
	{
		Mix_FreeMusic(song);
		song = NULL;
	}
	Mix_Quit();
}

void Player::togglePlay()
{
	
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
	
}


Player::Player()
{
	songIndex = 0;
	//music = nullptr;
	Player::initMixer();
	std::cout << "Constructor\n";
}
Player::~Player()
{
	Player::quitMixer();
	std::cout << "Destructor\n";
}

