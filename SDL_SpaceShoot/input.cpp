#include "input.h"
#


bool Input::GetKey(SDL_Scancode key)
{
	return keys_state[key].state;

}
