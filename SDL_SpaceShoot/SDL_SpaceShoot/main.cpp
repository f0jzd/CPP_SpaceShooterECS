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


using gridCell = std::vector<SDL_FRect*>;

using spatialHash = std::unordered_map<int, gridCell>;

spatialHash hashContainer;


using namespace std;

bool floatcomp(float i, float j)
{
	return (i < j);
}

const Entity MAX_ENTITIES = 1;

int activeProjectiles;

std::vector<Entity> allEntittys;

Entity createEntity()
{
	Entity entity = allEntittys.size();

	allEntittys.push_back(entity);
	

	return entity;
}

Entity gPlayerEntity;
std::vector<Entity> gEnemyEntities;

//std::vector<Entity> gEntityCopy(MAX_ENTITIES);
Entity gEntityCopy[MAX_ENTITIES]{}; //For handling collision checking thing


SDL_FRect gPlayerPos;
std::vector<SDL_FRect> gTransforms(MAX_ENTITIES);

std::vector<ProjectileEntity> gProjectileEntities(MAX_PROJECTILE_ENTITIES);
std::vector<SDL_FRect> gActiveProjectilePositions(MAX_PROJECTILE_ENTITIES);
std::vector<AABB> projectileAABBs (MAX_PROJECTILE_ENTITIES);

std::vector<AABB> colliders(MAX_ENTITIES);
//AABB colliders[MAX_ENTITIES]{};

//x_min check containers
//std::vector<float> collisions(MAX_ENTITIES);
float collisions[MAX_ENTITIES]{};

std::map<Entity, SDL_FRect> gEnemyData;

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
		gEnemyEntities.push_back(i);
	}


	for (size_t i = 0; i < MAX_ENTITIES; i++)
	{

		SDL_FRect pos = { rand() % gEngine.SCREEN_WIDTH,rand() % gEngine.SCREEN_HEIGHT, 50, 50 };

		gEnemyData.insert(std::pair<Entity,SDL_FRect>(i, pos));
	
		AABB enemyBox = AABB::make_from_position_size(gEnemyData[i].x + gEnemyData[i].w / 2, gEnemyData[i].y + gEnemyData[i].h / 2, gEnemyData[i].w, gEnemyData[i].h);

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
							createProj(gProjectileEntities, gActiveProjectilePositions, &gPlayerPos, activeProjectiles);
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

				//gEnemyData[0].x = gPlayerPos.x + 44;
				//gEnemyData[0].y = gPlayerPos.y;


				hashContainer.clear();

				gPlayer.updatePlayer(gInput, &gPlayerPos);

				//gSpatialHash.addObject(hashContainer,&gPlayerPos);

				for (int i = 0; i < gEnemyData.size(); i++)
				{
					gSpatialHash.addObject(hashContainer, &gEnemyData[i]);
				}

				gSpatialHash.checkCollisions(gEngine.gRenderer,hashContainer, &gPlayerPos);


				//Add a movement handler? maybe?

				SDL_RenderClear(gEngine.gRenderer);

				updateProj(gEngine.gRenderer, gProjectileEntities, gActiveProjectilePositions, activeProjectiles);


				for (size_t i = 0; i < gEnemyData.size(); i++)
				{
					gEnemyData[i].y -= 0;
				}

				for (int a = 0; a < gEnemyData.size(); a++) {

					AABB enemyBox = AABB::make_from_position_size(gEnemyData[a].x + gEnemyData[a].w / 2, gEnemyData[a].y + gEnemyData[a].h / 2, gEnemyData[a].w, gEnemyData[a].h);
					SDL_RenderCopyF(gEngine.gRenderer, gEngine.gEnemyTexture, &src, &gEnemyData[a]);
					AABB::Draw_box(gEngine.gRenderer, enemyBox);

				}

				auto playerBox = AABB::make_from_position_size(gPlayerPos.x + gPlayerPos.w / 2, gPlayerPos.y + gPlayerPos.h / 2, gPlayerPos.w, gPlayerPos.h);

				

				for (size_t i = 0; i < MAX_PROJECTILE_ENTITIES; i++)
				{
					if (gProjectileEntities[i].isActive)
					{
						for (size_t b = 0; b < MAX_ENTITIES; b++)
						{
							if (aabb_intersect(colliders[b], AABB::make_from_position_size(
								gActiveProjectilePositions[i].x + gActiveProjectilePositions[i].w / 2,
								gActiveProjectilePositions[i].y + gActiveProjectilePositions[i].h / 2,
								gActiveProjectilePositions[i].w,
								gActiveProjectilePositions[i].h)))
							{
								DeactivateProjectile(gProjectileEntities[i], gActiveProjectilePositions[i]);
								printf("asdf");
							}							
						}
					}
				}
		
				for (size_t i = 0; i < MAX_PROJECTILE_ENTITIES; i++)
				{
					SDL_RenderCopyF(gEngine.gRenderer, gEngine.gProjectileTexture, &src, &gActiveProjectilePositions[i]);
				}

				SDL_RenderCopyF(gEngine.gRenderer, gEngine.gPepeTexture, &src, &gPlayerPos);
				
				AABB::Draw_box(gEngine.gRenderer, playerBox);
				SDL_SetRenderDrawColor(gEngine.gRenderer, 0, 0, 0, 0);

				SDL_RenderPresent(gEngine.gRenderer);

				/*frame_time = SDL_GetTicks() - start_time;

				fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;	

				printf("%f", fps);*/

			}
		}
	}

	gEngine.close();

	return 0;
}

