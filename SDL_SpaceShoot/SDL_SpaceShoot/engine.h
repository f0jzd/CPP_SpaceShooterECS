#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <bitset>
#include <vector>

using Entity = std::uint32_t;

const Entity MAX_PROJECTILE_ENTITIES = 5;


extern Uint32 start_time, frame_time;
extern float fps;

extern float delta_time;
extern int frameNumber;

struct Engine
{
	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 640;

	//Loads individual image as texture
	SDL_Texture* loadTexture(std::string path);

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Current displayed texture
	SDL_Texture* gPepeTexture = NULL;
	SDL_Texture* gEnemyTexture = NULL;
	SDL_Texture* gProjectileTexture = NULL;



	//The surface contained by the window
	SDL_Surface* gScreenSurface = NULL;

	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	

};

struct ProjectileEntity
{
	Entity id;
	bool isActive;

};

