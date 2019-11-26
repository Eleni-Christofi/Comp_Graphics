#pragma once
#include "vector.h"
#include "object.h"
#include "lights.h"
#include "hit.h"
#include <vector>

using namespace std;

class Scene
{
public:
	float ka;
	Object *objects;
	vector<Light*> lights;

	//constructor (no objects, no lights, ambient light at 0.2)
	Scene()
	{
		objects = 0;
		lights = vector<Light*>();
		ka = 0.4;
	}

	//get value of colour and depth for each pixel 
	vector<float> get_pixel(Ray &ray);

	hit closest_intersection(Ray ray);

	Vector specular_diffuse(Hit closest)

};

