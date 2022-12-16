/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "engine.h"
#include "player.h"
#include "input.h"
#include <vector>
#include <time.h>
#include <map>
#include <algorithm>
#include "collisionHandler.h"
#include <iostream>
#include "customAlgorithms.h"
#include "projectileHandler.h"
#include "Quadtree.h"
#include "SpatialHash.h"


using gridCell = std::vector<EntityPosition*>;

using spatialHash = std::unordered_map<int, gridCell>;

spatialHash hashContainer;


using namespace std;

const Entity MAX_ENTITIES = 10;

int activeProjectiles;

Entity gPlayerEntity;
std::vector<Entity> gEnemyEntities(MAX_ENTITIES);

SDL_FRect gPlayerPos;

std::vector<AABB> colliders(MAX_ENTITIES);

float collisions[MAX_ENTITIES]{};

std::map<Entity, EntityPosition> gEnemyData;
std::map<Entity, EntityPosition> gProjectileData;



int main(int argc, char* args[])
{

	Uint64 previousTicks = SDL_GetPerformanceCounter();
	srand(time(NULL));


	Engine gEngine;
	Player gPlayer;
	Input gInput;


	SpatialHash gSpatialHash;


	for (size_t i = 0; i < MAX_ENTITIES; i++)
	{

		SDL_FRect pos = { rand() % gEngine.SCREEN_WIDTH,rand() % gEngine.SCREEN_HEIGHT, 50, 50 };
		
		EntityPosition s{ pos,true };

		gEnemyData.insert(std::pair<Entity, EntityPosition>(i, s));

		AABB enemyBox = AABB::make_from_position_size(gEnemyData[i].position.x + gEnemyData[i].position.w / 2, gEnemyData[i].position.y + gEnemyData[i].position.h / 2, gEnemyData[i].position.w, gEnemyData[i].position.h);

		colliders[i] = enemyBox;

	}
		

	
	if (!gEngine.init())
	{
		printf("Failed to inisitalize");

	}
	else
	{
		//Sets a defaault black bg colour

		if (!gEngine.loadMedia())
		{
			printf("Failed to laod media");
		}
		else
		{
			//--,src,--,dest

			SDL_Rect src = { 0,0, 112,112 };
			SDL_Rect projSrc = { 0,0, 64,64 };
			gPlayerPos = { (float)(gEngine.SCREEN_WIDTH / 2) - 25, ((float)gEngine.SCREEN_HEIGHT / 2) - 25, 50,50 };


			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			bool quit = false;
			SDL_Event e;

			while (!quit)
			{

				//start_time = SDL_GetTicks();

				

				frameNumber++;

				Uint64 ticks = SDL_GetPerformanceCounter();
				Uint64 deltaTicks = ticks - previousTicks;
				previousTicks = ticks;
				delta_time = (float)deltaTicks / SDL_GetPerformanceFrequency();


				while (SDL_PollEvent(&e))//puuting if here works, but then it only reads one event while using the while keeps handling more than one event in the queue?
				{
					switch (e.type)
					{
					case SDL_QUIT:
						quit = true;
						break;
					case SDL_KEYDOWN:
					{
						if (e.key.repeat)
						{
							break;
						}

						int scancode = e.key.keysym.scancode;

						if (scancode == SDL_SCANCODE_SPACE)
						{

							if (activeProjectiles >= 5)
								activeProjectiles = 0;
							//increment active projeectiles corresponding to their index?
							createProj(gProjectileData, &gPlayerPos, activeProjectiles);
							activeProjectiles++;


						}

						if (scancode == SDL_SCANCODE_ESCAPE)
							quit = true;

						gInput.keys[scancode] = true;
						gInput.keys_state[scancode].state = true;
						break;
					}
					case SDL_KEYUP:
					{
						int scancode = e.key.keysym.scancode;
						gInput.keys_state[scancode].state = false;
						gInput.keys[scancode] = false;
						break;

					}
					}
				}

				


				hashContainer.clear();

				gPlayer.updatePlayer(gInput, &gPlayerPos);


				for (int i = 0; i < gEnemyData.size(); i++)
				{
					gSpatialHash.addObject(hashContainer, &gEnemyData[i]);
				}

				gSpatialHash.checkCollisions(gEngine.gRenderer,hashContainer, &gPlayerPos);

				
				//Add a movement handler? maybe?

				SDL_RenderClear(gEngine.gRenderer);

				updateProj(gEngine.gRenderer, gProjectileData, activeProjectiles);


				
				for (int i = 0; i < gEnemyData.size(); i++)
				{
					auto targetDirectionX = gPlayerPos.x - gEnemyData[i].position.x;
					auto targetDirectionY = gPlayerPos.y - gEnemyData[i].position.y;
					
					gEnemyData[i].position.x += targetDirectionX * 0.5 * delta_time;
					gEnemyData[i].position.y += targetDirectionY * 0.5 * delta_time;

				}

				for (size_t i = 0; i < MAX_PROJECTILE_ENTITIES; i++)
				{

					if (gSpatialHash.checkCollisions(gEngine.gRenderer, hashContainer, gProjectileData[i]));
						//do optional collision stuff here
					
				}


				for (int a = 0; a < gEnemyData.size(); a++) {
					if (gEnemyData[a].isActive)
					{
						AABB enemyBox = AABB::make_from_position_size(gEnemyData[a].position.x + gEnemyData[a].position.w / 2, gEnemyData[a].position.y + gEnemyData[a].position.h / 2, gEnemyData[a].position.w, gEnemyData[a].position.h);
						SDL_RenderCopyF(gEngine.gRenderer, gEngine.gEnemyTexture, &src, &gEnemyData[a].position);
						AABB::Draw_box(gEngine.gRenderer, enemyBox);
					}

				}

				auto playerBox = AABB::make_from_position_size(gPlayerPos.x + gPlayerPos.w / 2, gPlayerPos.y + gPlayerPos.h / 2, gPlayerPos.w, gPlayerPos.h);


				

				
		
				for (size_t i = 0; i < MAX_PROJECTILE_ENTITIES; i++)
				{
					SDL_RenderCopyF(gEngine.gRenderer, gEngine.gProjectileTexture, &src, &gProjectileData[i].position);
				}

				SDL_RenderCopyF(gEngine.gRenderer, gEngine.gPepeTexture, &src, &gPlayerPos);
				
				AABB::Draw_box(gEngine.gRenderer, playerBox);
				SDL_SetRenderDrawColor(gEngine.gRenderer, 0, 0, 0, 0);

				SDL_RenderPresent(gEngine.gRenderer);
			}
		}
	}

	gEngine.close();

	return 0;
}

