#pragma once
#include "vector.h"
#include "object.h"
#include <vector>

using namespace std;

class Scene
{
public:
	Vector ambient_col;
	std::vector<Object*> objects;


	Vector get_pixel_colour(Ray ray) {};
	float get_pixel_depth(Ray ray) {};

};
