#pragma once
#include <SDL.h>


struct Input
{
	//Key press surfaces constants
	enum KeyPressSurfaces
	{
		KEY_PRESS_SURFACE_DEFAULT,
		KEY_PRESS_SURFACE_UP,
		KEY_PRESS_SURFACE_DOWN,
		KEY_PRESS_SURFACE_LEFT,
		KEY_PRESS_SURFACE_RIGHT,
		KEY_PRESS_SURFACE_TOTAL
	};

	bool GetKey(SDL_Scancode Key);

	struct KeyState
	{
		bool state = false; //basic bool to check if the key is pressed
		int changeFrame = 0;
	};

	KeyState keys_state[SDL_NUM_SCANCODES];
	bool keys[SDL_NUM_SCANCODES] = { false };
};