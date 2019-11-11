#pragma once
#include "vector.h"
#include "object.h"
#include <vector>

using namespace std;

class Scene
{
public:
	Vector ambient_col;
	Object *objects;

	Scene()
	{
		objects = 0;
		ambient_col.x = 255 * 0.2;
		ambient_col.y = 255 * 0.2;
		ambient_col.z = 255 * 0.2;
	}


	Vector get_pixel_colour(Ray ray);
	float get_pixel_depth(Ray ray);

};
