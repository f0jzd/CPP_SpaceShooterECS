#include "engine.h"




Uint32 start_time = 0, frame_time = 0;
float fps = 0;
float delta_time = 0.f;
int frameNumber;

bool Engine::init()
{
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL_TUT", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Failed");
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

			if (gRenderer == NULL)
			{
				printf("Renderer Failed");
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 255, 0xFF, 0xFF, 255);
				int imgFlags = IMG_INIT_PNG;

				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

			}
		}
	}

	return success;

}

SDL_Texture* Engine::loadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("unable to load image");
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("failed to create texture");

		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

bool Engine::loadMedia()
{

	bool success = true;

	gPepeTexture = loadTexture("Image/dffsdsd.png");
	
	gEnemyTexture = loadTexture("Image/despair.png");

	gProjectileTexture = loadTexture("Image/projectile.png");
	
	
	if (gPepeTexture == NULL || gEnemyTexture == NULL)
	{
		printf("Failed to load image");
		success = false;
	}


	return success;
}

void Engine::close()
{
	SDL_DestroyTexture(gPepeTexture);

	gPepeTexture = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();

}



