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

vector<float> Scene::get_pixel(Ray &ray, int depth)
{
	//find closest intersection point
	Hit closest;
	closest = closest_intersection(ray);

	//if we have actually hit something
	if (closest.flag && closest.t != FLT_MAX)
	{
		Vector colour = Vector();

		//add lighting effect (ignore if in shadow)
		colour = add_lighting(ray, closest, depth, colour, closest.what-> type);

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
	return closest;
}

Vector Scene::add_lighting(Ray ray, Hit closest, int depth, Vector colour, int type)
{

	if (depth < 0 || depth > max_depth)
	{
		//cout << "depth not in range" << depth << endl;
		return colour;
	}
	if (type == 0)
	{
		for (int i{ 0 }; i < lights.size(); i++)
		{
			Vector reflection = Vector();
			Vector light_direction = Vector();
			//if we are in shadow and on the correct side of the light, do not add specular and diffuse
			if (in_shad(closest, lights[i]))
			{
				continue;
			}


			//if we are not in shadow, calculate specular and diffuse components
			
			light_direction = lights[i]->get_direction(closest.position);

			float diffuse_component = light_direction.dot(closest.normal);
				if (diffuse_component < 0) 
				{
					continue;
				}



			colour.x += closest.what->colour.x * diffuse_component * closest.what->kd;
			colour.y += closest.what->colour.y * diffuse_component * closest.what->kd;
			colour.z += closest.what->colour.z * diffuse_component * closest.what->kd;

			
			closest.normal.reflection(light_direction, reflection);
			float specular_component = reflection.dot(ray.direction);
			if (specular_component < 0) specular_component = 0;

			//add specular component
			colour.x += closest.what->colour.x * pow(specular_component, 50) * closest.what->ks;
			colour.y += closest.what->colour.y * pow(specular_component, 50) * closest.what->ks;
			colour.z += closest.what->colour.z * pow(specular_component, 50) * closest.what->ks;

			colour = colour + ambient;
		}
		return colour;
	}
	else if(type == 1)
	{
		//cout << "type = 1 adding reflection " << endl;
		Vector reflection = Vector();
		reflection = reflect(ray.direction, closest);
		Ray refl_ray = Ray();
		refl_ray.position = closest.position + reflection * 0.001;
		refl_ray.direction = reflection;
		vector<float> recurse = get_pixel(refl_ray, depth + 1);
		Vector refl_col = Vector(recurse[1], recurse[2], recurse[3]);
		colour = colour + refl_col * closest.what->kr;
		type = 0;
		Vector spec_dif = add_lighting(ray, closest, depth, colour, type);
		colour = colour + spec_dif;
		return colour;

	}
	/*else
	{
		cout << "type =" << closest.what->type << " adding reflection/refraction" << endl;
		if (depth < max_depth && depth > 0)
		{
			float kr, kt;
			Vector refl_col = Vector();
			Vector refr_col = Vector();
			fresnel(ray, closest, kr, kt);

			if (kr < 1)
			{
				Ray refraction(closest.position, refract(ray.direction, closest));
				refraction.position = closest.position + refraction.direction * 0.001;
				refr_col = add_lighting(refraction, closest, depth + 1);
			}

			Vector new_dir = Vector();
			ray.direction.reflection(closest.normal, new_dir);
			Ray reflection(closest.position, new_dir);
			reflection.position = closest.position + reflection.direction * 0.001;
			refl_col = add_lighting(reflection, closest, depth + 1);
			colour = colour + refl_col * (kr*closest.what->kr) + refr_col * (1 - kr);
			colour = colour + ambient;
			cout << colour.x << " " << colour.y << " " << colour.z << endl;
			return colour;
		}
		

	}
	*/
	cout << "no lighting, depth is " << depth << endl;
	cout << colour.x << " " << colour.y << " " << colour.z << endl;
	return colour;
}

bool Scene::in_shad(Hit closest, Light* light)
{
	//finding out if the point is lit or in shadow
	Ray shad_ray;
	shad_ray.position = closest.position;
	shad_ray.direction = light->position - closest.position;

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
		if (shad_hit.flag && shad_hit.t < t)
		{
			return true;
		}
		shad_obj = shad_obj->next;
	}
	return false;
}

Vector Scene::reflect(Vector dir, Hit closest)
{
	Vector new_dir;
	new_dir = dir - closest.normal * 2 * closest.normal.dot(dir);
	return new_dir;
}

Vector Scene::refract(Vector dir, Hit closest)
{
	float n1 = 1;
	float n2 = closest.what->ri;
	Vector n = closest.normal;
	float cosi = dir.dot(closest.normal);
	if (cosi > 1) cosi = 1.0f;
	if (cosi < -1) cosi = -1.0f;
	if (cosi < 0) cosi = -cosi;
	else
	{
		swap(n1, n2);
		n.negate();
	}
	float div = n1 / n2;
	float cost = 1 - div * div*(1 - cosi * cosi);

	if (cost < 0) return Vector(0, 0, 0);
	else return Vector(dir*div + n * (sqrtf(cost) - div * cosi));

}

void Scene::fresnel(Ray ray, Hit closest, float r, float t)
{
	float n2 = closest.what->ri;
	r = closest.what->kr;
	t = closest.what->kt;

	float cosi = ray.direction.dot(closest.normal);
	if (cosi > 1) cosi = 1;
	if (cosi < -1) cosi = -1;
	float n1 = 1;
	if (cosi > 0) swap(n1, n2);
	float div = n1 / n2;
	float k = 1 - div * div*(1 - cosi * cosi);

	//check for total internal reflection 
	if (k < 0) r = 1;
	else
	{
		float cost = sqrtf(k);
		cosi = fabsf(cosi);

		float Rs = ((div*cosi) - cost) / ((div * cosi) + cost);
		float Rp = (cosi - (div*cost)) / (cosi + (div*cost));

		r = ((Rs*Rs) + (Rp*Rp)) / 2;
	}
	t = 1 - r;
}



