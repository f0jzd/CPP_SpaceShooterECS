
#include "collisionHandler.h"
#include "math.h"

const float PI = 3.1415;
const float TAU = 6.28318530718;

void draw_circle(SDL_Renderer* render, const Circle& c)
{
	int resolution = 100;

	float step = (PI * 2) / resolution;

	for (size_t i = 0; i < resolution; ++i)
	{
		float angle = step * i;
		float x1 = cos(angle);
		float y1 = sin(angle);

		float next_angle = step * (i + 1);

		float x2 = cos(next_angle);
		float y2 = sin(next_angle);

		SDL_RenderDrawLine(render,
			x1 * c.radius + c.x,
			y1 * c.radius + c.y,
			x2 * c.radius + c.x,
			y2 * c.radius + c.y
		);
	}
}

bool circle_intersect(const Circle& a, const Circle& b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;

	float dist_sqrd = dx * dx + dy * dy;
	float dist = sqrt(dist_sqrd);

	float radius_sum = a.radius + b.radius;

	return dist < radius_sum;
}




bool aabb_intersect(const AABB& a, const AABB& b)
{
	return (a.x_max > b.x_min &&
		b.x_max > a.x_min &&
		a.y_max > b.y_min &&
		b.y_max > a.y_min);

}

bool aabb_circle_intersect(const AABB& a, const Circle& b)
{
	float clamped_x = clamp(b.x, a.x_min, a.x_max);
	float clamped_y = clamp(b.y, a.y_min, a.y_max);

	float dx = b.x - clamped_x;
	float dy = b.y - clamped_y;

	float dist_sqrd = dx * dx + dy * dy;
	float dist = sqrt(dist_sqrd);

	return dist < b.radius;

}

bool aabb_point_intersect(const AABB& a, const Point& b)
{
	return (b.x < a.x_max&&
		b.x > a.x_min &&
		b.y < a.y_max&&
		b.y > a.y_min);
}

AABB AABB::make_from_position_size(float x, float y, float w, float h)
{

	AABB box;
	box.x_min = x - w / 2;
	box.x_max = x + w / 2;

	box.y_min = y - h / 2;
	box.y_max = y + h / 2;


	return box;
}

void AABB::Draw_box(SDL_Renderer* render, const AABB& box)
{
	SDL_Rect rect = {
		box.x_min,
		box.y_min,
		box.x_max - box.x_min,
		box.y_max - box.y_min
	};

	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	SDL_RenderDrawRect(render, &rect);
}




