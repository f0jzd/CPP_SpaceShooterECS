#pragma once
#include "engine.h"
#include <unordered_map>

struct SpatialHash
{
	
	SpatialHash();

	const int cellSize = 128;

	const int worldWidth = 640;
	const int worldHeight = 640;
	
	// Define the number of rows and columns in the grid.
	const int GRID_ROWS = worldWidth / cellSize;
	const int GRID_COLS = worldHeight / cellSize;


	int index;

	using gridCell = std::vector<EntityPosition*>;

	using spatialHash = std::unordered_map<int, gridCell>;

	void addObject(spatialHash& hash, EntityPosition* entity);

	bool checkCollisions(SDL_Renderer* render,spatialHash& hash, EntityPosition object);
	bool checkCollisions(SDL_Renderer* render,spatialHash& hash, SDL_FRect* object);


	int Hash(int x, int y);

private:
	int operator()(int a, int b);

};

