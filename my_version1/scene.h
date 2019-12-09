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
	Vector ambient;
	Object *objects;
	vector<Light*> lights;
	int max_depth;

	//constructor (no objects, no lights, ambient light at 0.2)
	Scene()
	{
		objects = 0;
		lights = vector<Light*>();
		ambient = Vector(0.7,0.7,0.7);
		max_depth = 5;
	}

	Scene(Vector amb_col, float ka, int d)
	{
		ambient = amb_col * ka;
		max_depth = d;
	}

	//get value of colour and depth for each pixel 
	vector<float> get_pixel(Ray &ray, int depth);

	Hit closest_intersection(Ray ray);

	Vector add_lighting(Ray ray, Hit closest, int d, Vector colour, int type);

	bool in_shad(Hit closest, Light* light);

	Vector reflect(Vector dir, Hit closest);

	Vector refract(Vector dir, Hit closest);

	void fresnel(Ray ray, Hit closest, float r, float t);



};

