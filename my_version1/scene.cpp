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
	//find closest intersection point
	Hit closest;
	closest = closest_intersection(ray);

	//if we have actually hit something
	if (closest.flag && closest.t != FLT_MAX)
	{
		Vector colour = Vector();

		//add specular & diffuse components/detect shadows
		colour = specular_diffuse(closest);


		//add ambient light
		colour.x += closest.what->colour.x * ka;
		colour.y += closest.what->colour.y * ka;
		colour.z += closest.what->colour.z * ka;

		

		//calculate depth & clamp 
		float t = 1 / closest.t;
		t = (t > 255) ? 255 : (t < 0.01) ? 0 : t;

		//return vector containing colour and depth
		vector<float> stuff{ colour.x,colour.y,colour.z, t };
		return stuff;
	}

	// if no hit, make everything black 
	vector<float> miss{ 0,0,0,0 };

	return miss;

}

Hit Scene::closest_intersection(Ray ray)
{
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
}

Vector Scene::specular_diffuse(Hit closest)
{
	Vector colour = Vector();
	//calculate cumulative light score
	for (int i{ 0 }; i < lights.size(); i++)
	{
		//finding out if the point is lit or in shadow
		Ray shad_ray;
		shad_ray.position = closest.position;
		shad_ray.direction = lights[i]->position - closest.position;

		float t = sqrt(shad_ray.direction.norm());
		
		//object intersection of ray from point of intersection to light
		shad_ray.direction.normalise();

		Hit shad_hit = Hit();
		shad_ray.position = shad_ray.position + shad_ray.direction * 0.001;

		/**cycle through all objects in scene */

		Object* shad_obj = objects;
		while (shad_obj != 0)
		{

			shad_obj->intersection(shad_ray, shad_hit);
			if (shad_hit.flag)
			{
				cout << "in shadow!" << endl;
				break;
			}
			shad_obj = shad_obj->next;
		}
		//if we are in shadow and on the correct side of the light, do not add specular and diffuse
		if (shad_hit.flag && shad_hit.t < t)
		{
			continue;
		}


		//if we are not in shadow, calculate specular and diffuse components
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

		//add specular component
		colour.x += closest.what->colour.x * pow(specular_component, 50) * closest.what->ks;
		colour.y += closest.what->colour.y * pow(specular_component, 50) * closest.what->ks;
		colour.z += closest.what->colour.z * pow(specular_component, 50) * closest.what->ks;

	}
	return colour;
}


