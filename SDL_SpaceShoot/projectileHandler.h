#pragma once
#include "engine.h"
#include <map>


void createProj(std::map<Entity, EntityPosition>& gProjectileData, SDL_FRect* playerPos, int& activeProj);

void updateProj(SDL_Renderer* render, std::map<Entity, EntityPosition>& projectilePos, int& activeProjectiles);

void DeactivateProjectile(ProjectileEntity gProjectiles, EntityPosition projectilePos);
