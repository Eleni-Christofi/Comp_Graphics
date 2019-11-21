#pragma once
#include "vector.h"
#include "object.h"
#include "lights.h"
#include <vector>

using namespace std;

class Scene
{
public:
	Vector ambient;
	Object *objects;
	vector<Light*> lights;

	//constructor (no objects, no lights, ambient light at 0.2)
	Scene()
	{
		objects = 0;
		lights = vector<Light*>();
		ambient.x = 0.2;
		ambient.y = 0.2;
		ambient.z = 0.2;
	}

	//get value of colour and depth for each pixel 
	vector<float> get_pixel(Ray &ray);


};

