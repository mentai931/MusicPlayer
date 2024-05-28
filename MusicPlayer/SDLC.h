#pragma once
#include "SDL.h"
#include "SDL_rwops.h"
#include "SDL_filesystem.h"


class SDLC
{
public:
	SDLC();
	~SDLC();
	bool endIt = false;

private:
	const unsigned short WINwidth = 1280, WINheight = 720;
	SDL_Rect Recti{ WINwidth / 2,WINheight / 2,50,50 };
	SDL_Rect backWards{ ((WINwidth / 2) - 70) ,WINheight / 2,50,50 };
	SDL_Rect forWards{ ((WINwidth / 2) + 70) ,WINheight / 2,50,50 };

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
	void input();
	

};

