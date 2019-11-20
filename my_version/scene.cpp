#include <iostream>

#include "scene.h"
#include "vector.h"
#include "object.h"
#include "ray.h"
#include "hit.h"
#include <float.h>
#include <math.h>
#include <vector>

using namespace std;

vector<float> Scene::get_pixel(Ray &ray)

	Vector colour = Vector();
	Hit closest;
	closest.t = FLT_MAX;
	Object* object = objects;

	//finding the closest intersection point 
	while (object != 0)
	{
		Hit hit;
		//perform object intersection for each object in the scene
		object->intersection(ray, hit);
		
		//if something is hit by the ray
		if (hit.flag)
		{
			//if the new t value is the smallest we keep it
			if (hit.t < closest.t && hit.t > 0.01)
			{
				closest = hit;
			}
		}
		//move to the next object in the scene
		object = object->next;
	}

	

	//if we have actually hit something
	if (closest.flag && closest.t != FLT_MAX)
	{


		//finding out if the point is lit or in shadow
		Ray shad_ray;
		float is_shad{ 1 };
		//cycle through all objects in scene
		while (object != 0)
		{
			Hit hit;
			//cycle through all lights in scene
			for (int i{ 0 }; i < lights.size(); i++)
			{

				shad_ray.position = closest.position;
				shad_ray.direction = lights[i].position - closest.position;

				//object intersection of ray from point of intersection to light
				object->intersection(ray, hit);
				//making sure to only check for intersections between object and light source 
				t = (lights[i].position - hit.position).norm();
				t = sqrt(t);
				if (!hit.flag)
				{
					if (hit.t < t && hit.t > 0.01)
					{
						is_shad = 0.1;
					}
				}
			}
		}


		//calculate colour & clamp values
		colour = closest.what->colour * closest.what->albedo / M_PI * lights->intensity * lights->colour * max(0.f, closest.normal.dot(L)*is_shad;
		colour.x = (colour.x > 1) ? 1 : (colour.x < 0) ? 0 : colour.x;
		colour.y = (colour.y > 1) ? 1 : (colour.y < 0) ? 0 : colour.y;
		colour.z = (colour.x > 1) ? 1 : (colour.z < 0) ? 0 : colour.z;
		
		//calculate depth & clamp 
		float t = 1 / closest.t;
		t = (t > 255) ? 255 : (t < 0.01) ? 0 : t;

		
		cout << "hit " << closest.t << endl;

		//return vector containing colour and depth
		vector<float> stuff{ colour.x,colour.y,colour.z, t };
		return stuff;
	}

	// if no hit, make everything black 
	vector<float> miss{ 0,0,0,0 };

	return miss;

}


