#include "SpatialHash.h"
#include "collisionHandler.h"


int SpatialHash::Hash(int x, int y)
{

	return (x % 10) + (y % 10);


	//return x + (y * GRID_COLS);
}

int SpatialHash::operator()(int a, int b)
{
	return a + b;
}



SpatialHash::SpatialHash()
{
}

void SpatialHash::addObject(spatialHash& hash, SDL_FRect* entity)
{
	int x = (entity->x) / cellSize;
	int y = (entity->y) / cellSize;

	int index = Hash(x, y);

	hash[index].push_back(entity);
}

void SpatialHash::checkCollisions(SDL_Renderer* render,spatialHash& hash, SDL_FRect* object)
{
	int x = object->x / cellSize;
	int y = object->y / cellSize;

	int index = Hash(x, y);

	printf("Player cell: %d\n", index);


	for (size_t i = 0; i < GRID_ROWS; i++)
	{
		for (size_t j = 0; j < GRID_COLS; j++)
		{

			int cellindex = Hash(x + i, y + j);

			std::vector<SDL_FRect*>& obj = hash[cellindex];

			// Check each object in the current cell for collisions with the object.
			for (auto other : obj)
			{
				AABB player = AABB::make_from_position_size(object->x + object->w, object->y + object->h, object->w, object->h);
				AABB enemy = AABB::make_from_position_size(other->x + other->w, other->y + other->h, other->w, other->h);

				if (aabb_intersect(player, enemy))
				{
					//printf("hello");
					//Do wahtever happens when colliding here.

				}
			}
		}
	}
	


	//for (auto it = hash.begin(); it != hash.end(); it++)
	//{

	//	int cellIndex = Hash(x+,x+j)


	//	printf("%d \n", it->first);
	//	printf("%d \n", it->second);
	//}


}
