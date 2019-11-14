#include <iostream>

#include "scene.h"
#include "vector.h"
#include "object.h"
#include "ray.h"
#include "hit.h"
#include <float.h>

float Scene::get_pixel_depth(Ray ray)
{
	Hit closest;
	closest.t = FLT_MAX;
	Object* object = objects;
	while(object!=0)
	{
		Hit hit;
		object->intersection(ray, hit);
		if (hit.flag)
		{
			if (hit.t < closest.t && hit.t > 0)
			{
				closest = hit;
			}
		}
		object = object->next;
	}

	if (closest.flag)
	{
		closest.t = (closest.t > 255) ? 255 : (closest.t < 0) ? 0 : closest.t;
		cout << "hit " << closest.t << endl;
		return 1/(closest.t);
	}

	return -1.0f;
	cout << "miss" << endl;
}

Vector Scene::get_pixel_colour(Ray ray)
{
	Vector colour;
	Hit closest;
	closest.t = FLT_MAX;
	Object* object = objects;
	while(object!=0)
	{
		Hit hit;
		object ->intersection(ray, hit);
		if (hit.flag)
		{
			if (hit.t < closest.t && hit.t > 0)
			{
				closest = hit;
			}
		}
		object = object->next;
	}
	colour = closest.what->colour;

	if (closest.flag)
	{
		colour.x = (colour.x > 255) ? 255 : (colour.x < 0) ? 0 : colour.x;
		colour.y = (colour.y > 255) ? 255 : (colour.y < 0) ? 0 : colour.y;
		colour.z = (colour.x > 255) ? 255 : (colour.z < 0) ? 0 : colour.z;
		return colour;
		cout << "hit " << colour.x << " " << colour.y << " " << colour.z << endl;
	}

	return Vector(0, 0, 0);
	cout << "miss" << endl;
}