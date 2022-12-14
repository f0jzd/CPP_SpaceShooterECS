#include "Quadtree.h"

Quadtree::Quadtree(int pLevel, SDL_FRect pBounds) : m_bounds(pBounds)
{
	m_level = pLevel;

}

void Quadtree::clear()
{
	objects.clear();

	for (int i = 0; i < 4; i++) {
		if (m_nodes[i] != nullptr)
		{
			m_nodes[i]->clear();
			delete m_nodes[i];

		}
			
	}
}

void Quadtree::split()
{
	auto subwidth = m_bounds.w / 2;
	auto subheight = m_bounds.h / 2;
	auto x = m_bounds.x;
	auto y = m_bounds.y;
	
	m_nodes[0] = new Quadtree(m_level + 1, SDL_FRect{x, y , subwidth, subheight});
	
	m_nodes[1] = new Quadtree(m_level + 1, SDL_FRect{x + subwidth, y, subwidth, subheight});
	
	m_nodes[2] = new Quadtree(m_level + 1, SDL_FRect{x, y + subheight, subwidth, subheight});
	
	m_nodes[3] = new Quadtree(m_level + 1, SDL_FRect{x+ subwidth, y + subheight, subwidth, subheight});
}

int Quadtree::getIndex(SDL_FRect rect)
{

	int index = -1;

	
	auto verticalMidpoint = m_bounds.x + m_bounds.w / 2;
	auto horizontalMidpoint = m_bounds.y + m_bounds.h / 2;

	// Object can completely fit within the top quadrants
	bool topQuadrant = rect.y < horizontalMidpoint&& rect.y + rect.h < horizontalMidpoint;

	bool bottomQuadrant = rect.y > horizontalMidpoint;
		
	if (rect.x < verticalMidpoint && rect.x + rect.w < verticalMidpoint)
	{
		if (topQuadrant)
		{
			index = 1;
		}
		else if (bottomQuadrant)
		{
			index = 2;
		}
	}
	else if (rect.x > verticalMidpoint)
	{
		if (topQuadrant)
		{
			index = 0;
		}
		else if (bottomQuadrant)
		{
			index = 3;
		}

	}
	return index;
}

void Quadtree::insert(SDL_FRect* rect)
{
	if (m_nodes[0] != nullptr)
	{
		int index = getIndex(*rect);

		if (index != -1)
		{
			m_nodes[index]->insert(rect);
			return;
		}

	}

	objects.push_back(rect);

	if (objects.size() > MAX_OBJECTS && m_level < MAX_LEVELS)
	{
		if (m_nodes[0] == nullptr)
		{
			split();
		}

		int i = 0;
		while (i < objects.size())
		{
			int index = getIndex(*objects[i]);
			if (index != -1)
			{
				m_nodes[index]->insert(*objects.erase(objects.begin() + index));
			}
			else 
			{
				i++;
			}
		}
	}
}

std::vector<SDL_FRect*> Quadtree::retrieve(std::vector<SDL_FRect*> returnVector, SDL_FRect* aabb)
{
	int index = getIndex(*aabb);

	if (index != -1 && m_nodes[0] == nullptr)
	{
		m_nodes[index]->retrieve(returnVector, aabb);
	}

	returnVector = objects;

	return returnVector;
}

//Quadtree::Quadtree(int level, SDL_FRect bounds) : m_bounds(bounds)
//{
//    m_level = level;
//    nodeFlag = false;
//
//    for (int i = 0; i < 4; i++) {
//        m_nodes[i] = nullptr;
//    }
//}
//
//bool Quadtree::canHold(SDL_FRect bounds, SDL_FRect* aabb)
//{
//    return (aabb->w < bounds.w && aabb->h < bounds.h);
//}
//
//void Quadtree::clear()
//{
//    objects.clear();
//
//    if (nodeFlag) {
//        for (int i = 0; i < 4; i++) {
//            m_nodes[i]->clear();
//            delete m_nodes[i];
//        }
//
//        nodeFlag = false;
//    }
//}
//
//void Quadtree::insert(SDL_FRect* aabb)
//{
//    if (objects.size() == MAX_OBJECTS && m_level != MAX_LEVELS) {
//        if (!nodeFlag) {
//            // Create child nodes
//            m_nodes[0] = new Quadtree(m_level + 1, SDL_FRect{ m_bounds.x, m_bounds.y, m_bounds.w / 2.f, m_bounds.h / 2.f });
//            m_nodes[1] = new Quadtree(m_level + 1, SDL_FRect{ m_bounds.x + m_bounds.h / 2.f, m_bounds.y, m_bounds.w / 2.f, m_bounds.h / 2.f });
//            m_nodes[2] = new Quadtree(m_level + 1, SDL_FRect{ m_bounds.x, m_bounds.y + m_bounds.h / 2.f, m_bounds.w / 2.f, m_bounds.h / 2.f });
//            m_nodes[3] = new Quadtree(m_level + 1, SDL_FRect{ m_bounds.x + m_bounds.w / 2.f, m_bounds.y + m_bounds.h / 2.f, m_bounds.w / 2.f, m_bounds.h / 2.f });
//            nodeFlag = true;
//        }
//
//        int index = getIndex(aabb);
//
//        if (index == -1) {
//            objects.push_back(aabb);
//        }
//        else {
//            m_nodes[index]->insert(aabb);
//        }
//    }
//    else {
//        objects.push_back(aabb);
//    }
//}
//
//void Quadtree::retrieve(std::vector<SDL_FRect*>& returnVector, SDL_FRect* aabb)
//{
//    for (int i = 0; i < objects.size(); i++) {
//        if (objects[i] != aabb) {
//            returnVector.push_back(objects[i]);
//        }
//    }
//
//    if (nodeFlag) {
//        int index = getIndex(aabb);
//
//        if (index != -1) {
//            m_nodes[index]->retrieve(returnVector, aabb);
//        }
//    }
//}
//
//int Quadtree::getIndex(SDL_FRect* aabb)
//{
//    int index = -1;
//
//    if (nodeFlag) {
//        for (int i = 0; i < 4; i++) {
//            if (m_nodes[i]->canHold(m_nodes[i]->m_bounds, aabb)) {
//                index = i;
//                break;
//            }
//        }
//    }
//
//    return index;
//}

