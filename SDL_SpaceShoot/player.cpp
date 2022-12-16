#include "input.h"
#include "player.h"
#include "engine.h"

void Player::updatePlayer(Input inpt, SDL_FRect* playerImg)
{
	
	if (inpt.GetKey(SDL_SCANCODE_RIGHT) || inpt.GetKey(SDL_SCANCODE_D))
	{
		playerImg->x += 200 * delta_time;
	}
	if (inpt.GetKey(SDL_SCANCODE_LEFT) || inpt.GetKey(SDL_SCANCODE_A))
	{
		playerImg->x -= 200 * delta_time;
	}
	if (inpt.GetKey(SDL_SCANCODE_UP) || inpt.GetKey(SDL_SCANCODE_W) )
	{
		playerImg->y -= 200 * delta_time;
	}
	if (inpt.GetKey(SDL_SCANCODE_DOWN) || inpt.GetKey(SDL_SCANCODE_S))
	{
		playerImg->y += 200 * delta_time;
	}

}
