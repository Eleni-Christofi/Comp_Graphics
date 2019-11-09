#include "Scene.h"
#include "vector.h"
#include "object.h"
#include "ray.h"
#include "hit.h"

Vector Scene::get_pixel_depth(Ray ray)
{
	Hit* closest;
	closest.t = FLT_MAX;
	for (int i{ 0 }; i < objects.size; i++)
	{
		Hit hit;
		scene_objects[i].intersection(ray, hit);
		if (hit.flag)
		{
			if (hit.t < closest.t && hit.t > 0)
			{
				closest = hit;
			}
		}

	}

	if (closest.flag)
	{
		closest.t = (closest.t > 255) ? 255 : (closest.t < 0) ? 0 : closest.t;
		return closest.t;
	}

	return Vector(0, 0, 0);
}

Vector Scene::get_pixel_colour(Ray ray)
{
	Hit* closest;
	closest.t = FLT_MAX;
	for (int i{ 0 }; i < objects.size; i++)
	{
		Hit hit;
		scene_objects[i].intersection(ray, hit);
		if (hit.flag)
		{
			if (hit.t < closest.t && hit.t > 0)
			{
				closest = hit;
			}
		}

	}

	if (closest.flag)
	{
		closest.colour.x = (closest.colour.x > 255) ? 255 : (closest.colour.x < 0) ? 0 : closest.colour.x;
		closest.colour.y = (closest.colour.y > 255) ? 255 : (closest.colour.y < 0) ? 0 : closest.colour.y;
		closest.colour.z = (closest.colour.x > 255) ? 255 : (closest.colour.z < 0) ? 0 : closest.colour.z;
		return closest.colour;
	}

	return Vector(0, 0, 0);
}