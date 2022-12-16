#pragma once
#include "engine.h"

struct Circle
{
	float x;
	float y;
	float radius;
};


struct Point
{
	float x;
	float y;
};

//void draw_circle(const Circle& circle);
bool circle_intersect(const Circle& a, const Circle& b);

struct AABB
{
	static AABB make_from_position_size(float x, float y, float w, float h); //Call it as a part of the class, similar to namespace, treats the class as a namespace.
	static void Draw_box(SDL_Renderer* render, const AABB& box);

	float x_min;
	float y_min;

	float x_max;
	float y_max;

};

//void draw_filled_box(const AABB& box);
bool aabb_intersect(const AABB& a, const AABB& b);

bool aabb_circle_intersect(const AABB& a, const Circle& b);

bool aabb_point_intersect(const AABB& a, const Point& b);