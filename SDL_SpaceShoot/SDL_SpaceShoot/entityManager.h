//#pragma once
//#include "engine.h"
//#include <queue>
//#include <cassert>
//
//using Entity = std::uint32_t;
//const Entity MAX_ENTITIES = 50;
//
//struct Transform
//{
//	SDL_FRect pos;
//};
//
//using ComponentType = std::uint8_t;
//
//const ComponentType MAX_COMPONENTS = 32;
//
//using Signature = std::bitset<MAX_COMPONENTS>;
//
//class EntityManager
//{
//public:
//	EntityManager()
//	{
//		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
//		{
//			mAvailableEntities.push(entity);
//		}
//	}
//
//	Entity CreateEntity()
//	{
//		assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");
//
//		Entity id = mAvailableEntities.front();
//		mAvailableEntities.pop();
//		++mLiningEntityCount;
//
//		return id;
//	}
//
//	void DestroyEntity(Entity entity)
//	{
//		assert(entity < MAX_ENTITIES && "Entity outt of range.");
//		mSignatures.push(entity);
//		
//	}
//
//private:
//
//	std::queue<Entity> mAvailableEntities{};
//	std::array<Signature, MAX_ENTITIES> mSignatures{};
//
//	uint32_t mLiningEntityCount{};
//};
//
