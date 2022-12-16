#include "projectileHandler.h"
#include "collisionHandler.h"


void createProj(std::map<Entity, EntityPosition>& gProjectileData,SDL_FRect* playerPos,int &activeProj)
{
	gProjectileData[activeProj].isActive = true;
	gProjectileData[activeProj].position = *playerPos;
}

void updateProj(SDL_Renderer* render, std::map<Entity, EntityPosition>& projectilePos,int &activeProjectiles)
{
	for (size_t i = 0; i < MAX_PROJECTILE_ENTITIES; i++)
	{
		if (projectilePos[i].isActive)
			projectilePos[i].position.y -= 100 * delta_time;
		

		if (projectilePos[i].position.y < -100)
			projectilePos[i].isActive = 0;

		AABB::Draw_box(render, AABB::make_from_position_size(
			projectilePos[i].position.x+ projectilePos[i].position.w/2,
			projectilePos[i].position.y+ projectilePos[i].position.h/2,
			projectilePos[i].position.w,
			projectilePos[i].position.h
			));
		
	}
}

void DeactivateProjectile(ProjectileEntity gProjectiles, EntityPosition projectilePos)
{
	projectilePos.isActive = false;
	projectilePos.position = { -100,-100,projectilePos.position.w,projectilePos.position.h };
}
