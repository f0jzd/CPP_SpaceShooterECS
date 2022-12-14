#include "projectileHandler.h"
#include "collisionHandler.h"
//void updateProj(int& currentProjectile,std::vector<ProjectileEntity>& gActiveProjectiles,float speed)
//{
//	for (auto var: gActiveProjectiles)
//	{
//		if (var.isActive)
//		{
//			var.position->y += speed;
//		}
//
//		if (var.position->y < 0)
//		{
//			var.isActive = false;
//		}
//	}
//
//}
//
//void createProj(int &currentProjectile,std::vector<ProjectileEntity> &gActiveProjectiles,SDL_FRect* playerPos)
//{
//	gActiveProjectiles[currentProjectile].isActive = true;
//	gActiveProjectiles[currentProjectile].position = playerPos;
//
//}

void createProj(std::vector<ProjectileEntity> &gProjectiles, std::vector<SDL_FRect> &gProjecilePos,SDL_FRect* playerPos,int activeProj)
{
	
	gProjectiles[activeProj].id = activeProj;
	gProjectiles[activeProj].isActive = true;
	gProjecilePos[activeProj] = *playerPos;

}

void updateProj(SDL_Renderer* render,std::vector<ProjectileEntity> &gProjectiles, std::vector<SDL_FRect> &gProjecilePos,int &activeProjectiles)
{
	for (size_t i = 0; i < MAX_PROJECTILE_ENTITIES; i++)
	{
		if (gProjectiles[i].isActive)
			gProjecilePos[i].y -= 100 * delta_time;

		if (gProjecilePos[i].y < -100)
			gProjectiles[i].isActive = 0;

		AABB::Draw_box(render, AABB::make_from_position_size(
			gProjecilePos[i].x+ gProjecilePos[i].w/2,
			gProjecilePos[i].y+ gProjecilePos[i].h/2,
			gProjecilePos[i].w,
			gProjecilePos[i].h
			));
		
	}
}

void DeactivateProjectile(ProjectileEntity gProjectiles,SDL_FRect& gProjecilePos)
{
	gProjectiles.isActive = false;
	gProjecilePos = { -100,-100,gProjecilePos.w,gProjecilePos.h };
}
