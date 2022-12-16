#pragma once
#include "engine.h"
#include "collisionHandler.h"

class Quadtree {

public:
	//Quadtree();

	Quadtree(int pLevel, SDL_FRect bounds);

	//Quadtree(int level, SDL_FRect& bounds);

	//Quadtree(int level, SDL_FRect& bounds);

	bool canHold(SDL_FRect bounds,SDL_FRect* aabb);

	void clear();

	//void retrieve(std::vector<SDL_FRect*>& returnVector, SDL_FRect* aabb);

	//int getIndex(SDL_FRect* aabb);

	void split();

	int getIndex(SDL_FRect rect);

	void insert(SDL_FRect* rect);

	std::vector<SDL_FRect*> retrieve(std::vector<SDL_FRect*> returnVector, SDL_FRect* aabb);

	///bool nodeFlag;

	static const int MAX_OBJECTS = 4;
	static const int MAX_LEVELS = 5;
	

	int m_level; // Level of recursion
	
	//Bounds that the box will cover.
	SDL_FRect m_bounds;
	std::vector<SDL_FRect*> objects;
	std::vector<Quadtree*> m_nodes;

	//bool node_flag; // flag to denote whether child nodes have been create dor not
	//Quadtree* m_nodes[4];

};


