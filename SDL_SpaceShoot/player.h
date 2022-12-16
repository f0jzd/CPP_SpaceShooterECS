#pragma once
#include "input.h"
#include <SDL.h>
#include <SDL_image.h>


class Player
{
public:

	struct PlayerPosition
	{
		float x;
		float y;
	} playerPos;

	struct PlayerGraphics
	{
		SDL_FRect playerImg;


	}playerGraphics;
	
	void updatePlayer(Input input, SDL_FRect* playerImg);


};