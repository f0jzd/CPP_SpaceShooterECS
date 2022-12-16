#include "SpatialHash.h"
#include "collisionHandler.h"


int SpatialHash::Hash(int x, int y)
{
	std::string a = std::to_string(x) + std::to_string(y);

	return std::hash<std::string>()(a);

	//return (x % 10) + (y % 10);


	//return x + (y * GRID_COLS);
}

int SpatialHash::operator()(int a, int b)
{
	return a + b;
}



SpatialHash::SpatialHash()
{
}

void SpatialHash::addObject(spatialHash& hash, EntityPosition* entity)
{
	int x = (entity->position.x) / cellSize;
	int y = (entity->position.y) / cellSize;

	int index = Hash(x, y);

	hash[index].push_back(entity);
}




bool SpatialHash::checkCollisions(SDL_Renderer* render,spatialHash& hash, EntityPosition object)
{
	int x = object.position.x / cellSize;
	int y = object.position.y / cellSize;

	

	int index = Hash(x, y);

	//printf("Player cell: %d\n", index);


	for (size_t i = 0; i < GRID_ROWS; i++)
	{
		for (size_t j = 0; j < GRID_COLS; j++)
		{

			int cellindex = Hash(x + i, y + j);

			std::vector<EntityPosition*>& obj = hash[cellindex];

			// Check each object in the current cell for collisions with the object.
			for (auto other : obj)
			{
				
				AABB player = AABB::make_from_position_size(object.position.x + object.position.w, object.position.y + object.position.h, object.position.w, object.position.h);
				AABB enemy = AABB::make_from_position_size(other->position.x + other->position.w, other->position.y + other->position.h, other->position.w, other->position.h);

				if (aabb_intersect(player, enemy))
				{

					other->isActive = false;

					return true;
					//printf("hello");
					//Do wahtever happens when colliding here.

				}
			}
		}
	}

	return false;

}

bool SpatialHash::checkCollisions(SDL_Renderer* render, spatialHash& hash, SDL_FRect* object)
{
	int x = object->x / cellSize;
	int y = object->y / cellSize;



	int index = Hash(x, y);

	//printf("Player cell: %d\n", index);


	for (size_t i = 0; i < GRID_ROWS; i++)
	{
		for (size_t j = 0; j < GRID_COLS; j++)
		{

			int cellindex = Hash(x + i, y + j);

			std::vector<EntityPosition*>& obj = hash[cellindex];

			// Check each object in the current cell for collisions with the object.
			for (auto other : obj)
			{

				AABB player = AABB::make_from_position_size(object->x + object->w, object->y + object->h, object->w, object->h);
				AABB enemy = AABB::make_from_position_size(other->position.x + other->position.w, other->position.y + other->position.h, other->position.w, other->position.h);

				if (aabb_intersect(player, enemy))
				{
					
					other->isActive = false;

					return true;
					//printf("hello");
					//Do wahtever happens when colliding here.

				}
			}
		}
	}

	return false;
}
