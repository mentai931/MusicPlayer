#pragma once
#include <vector>
#include "SDL2_mixer/include/SDL_mixer.h"
#include <iostream>
#include <string>

class Player
{
private:
	 
	 Mix_Music* music;
	const std::string musicPath;
	int result = 0;
	bool playing;
	
public:
	unsigned int songIndex = 0;
	std::vector<Mix_Music*> songs;

public:
	bool initMixer();
	void quitMixer();
	bool playMusic(int index);
	int loadMusic(const char* filename);
	void togglePlay();
	Player();
	~Player();

	
};