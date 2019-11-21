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
{
	Vector colour = Vector();
	Hit closest;
	closest.t = FLT_MAX;
	Object* object = objects;
	float ka = 0.4;

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
		//cout << closest.what->kd << endl;

		//finding out if the point is lit or in shadow
		Ray shad_ray;
		/**cycle through all objects in scene
		while (object != 0)
		{
			Hit hit;
			//cycle through all lights in scene
			for (int i{ 0 }; i < lights.size(); i++)
			{
				vector<float> is_shad(lights.size);
				shad_ray.position = closest.position;
				shad_ray.direction = lights[i]->position - closest.position;

				//object intersection of ray from point of intersection to light
				object->intersection(ray, hit);
				//making sure to only check for intersections between object and light source 
				float t = (lights[i] -> position - hit.position).norm();
				t = sqrt(t);
				if (!hit.flag)
				{
					if (hit.t < t && hit.t > 0.01)
					{
						is_shad[i] = 0.1;
					}
				}
			}
		}
		*/


		//calculate cumulative light score
		for (int i{ 0 }; i < lights.size(); i++)
		{
			//light = light + lights[i]->colour*lights[i]->intensity*max(0.0f, closest.normal.dot(lights[i]->get_direction(closest.position)); //* is_shad[i];
			//closest.normal.negate();
			Vector light_direction = lights[i]->get_direction(closest.position);

			float diffuse_component = light_direction.dot(closest.normal);
			if (diffuse_component < 0) {
				continue;
			}

			colour.x += closest.what->colour.x * diffuse_component * closest.what->kd;
			colour.y += closest.what->colour.y * diffuse_component * closest.what->kd;
			colour.z += closest.what->colour.z * diffuse_component * closest.what->kd;
			
			Vector reflection = Vector();
			closest.normal.reflection(light_direction, reflection);
			float specular_component = reflection.dot(ray.direction);
			if (specular_component < 0) specular_component = 0;

			colour.x += closest.what->colour.x * pow(specular_component, 50) * closest.what->ks;
			colour.y += closest.what->colour.y * pow(specular_component, 50) * closest.what->ks;
			colour.z += closest.what->colour.z * pow(specular_component, 50) * closest.what->ks;
			//cout << colour.x << colour.y << colour.z << endl;
		}

		//calculate colour & clamp values
		colour.x += closest.what->colour.x * ka;
		colour.y += closest.what->colour.y * ka;
		colour.z += closest.what->colour.z * ka;

		//cout << colour.x << colour.y << colour.z << endl;
		
		// colour.x = (colour.x > 1) ? 1 : (colour.x < 0) ? 0 : colour.x;
		// colour.y = (colour.y > 1) ? 1 : (colour.y < 0) ? 0 : colour.y;
		// colour.z = (colour.x > 1) ? 1 : (colour.z < 0) ? 0 : colour.z;
		
		//calculate depth & clamp 
		float t = 1 / closest.t;
		t = (t > 255) ? 255 : (t < 0.01) ? 0 : t;

		
		//cout << "hit " << closest.t << endl;

		//return vector containing colour and depth
		vector<float> stuff{ colour.x,colour.y,colour.z, t };
		return stuff;
	}

	// if no hit, make everything black 
	vector<float> miss{ 0,0,0,0 };

	return miss;

}


