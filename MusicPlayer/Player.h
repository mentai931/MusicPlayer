#pragma once
#include <vector>
#include "SDL2_mixer/include/SDL_mixer.h"
#include <iostream>
#include <string>

class Player
{
private:
	std::vector<Mix_Music*> songs;
	Mix_Music* music;
	const std::string musicPath;
	int result = 0;
	bool playing;

public:
	bool initMixer();
	void quitMixer();
	bool playMusic(int index);
	int loadMusic(const char* filename);
	void togglePlay();
	Player();
	~Player();

	static void songFinished();
};