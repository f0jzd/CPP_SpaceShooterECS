# CPP_SpaceShooterECS
 
This space shooter was an attempt at creating an ecs system, and managed to get most of it working to a certain degree. 

The game uses maps to map entites and their respective values to change and manage their positions.

```cpp
Entity gPlayerEntity;
std::vector<Entity> gEnemyEntities(MAX_ENTITIES);

SDL_FRect gPlayerPos;

std::vector<AABB> colliders(MAX_ENTITIES);

float collisions[MAX_ENTITIES]{};

std::map<Entity, EntityPosition> gEnemyData;
std::map<Entity, EntityPosition> gProjectileData;

```

This makes so that when i want to update certain projectiles or enemies and simply sent the entity id, which is an integer, and then update the respective id:s position.

```cpp
struct EntityPosition
{
	SDL_FRect position;
	bool isActive;

};
```

I used a custom AABB collision script to then handle the collision using the FRect since it has width and height aswell. I tried to also implement a spatial hash and it worked to some degree. 

```cpp
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
```
This was used to separate the screen into a grid system and use those to check collisions. This was my first time implementing a spatial hash so it did not manage to work "perfect", but it worked to some degree. 



