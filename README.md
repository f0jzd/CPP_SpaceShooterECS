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
