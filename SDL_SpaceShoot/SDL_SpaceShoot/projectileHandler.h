#pragma once
#include "engine.h"

//void updateProj(int& currentProjectile, std::vector<SDL_FRect> gActiveProjectiles, float speed);

//void createProj(int& currentProjectile, std::vector<ProjectileEntity>& gActiveProjectiles, SDL_FRect* playerPos);

void createProj (std::vector<ProjectileEntity> &gProjectiles, std::vector<SDL_FRect> &gProjecilePos, SDL_FRect* playerPos, int activeProj);

void updateProj (SDL_Renderer* render, std::vector<ProjectileEntity>& gProjectiles, std::vector<SDL_FRect>& gProjecilePos, int& activeProjectiles);

void DeactivateProjectile(ProjectileEntity gProjectiles, SDL_FRect& gProjecilePos);
