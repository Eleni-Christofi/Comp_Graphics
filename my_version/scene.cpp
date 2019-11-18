#include <iostream>

#include "scene.h"
#include "vector.h"
#include "object.h"
#include "ray.h"
#include "hit.h"
#include <float.h>

using namespace std;

vector<float> Scene::get_pixel(Ray &ray)
{

	Vector colour = Vector();
	Hit closest;
	closest.t = FLT_MAX;
	Object* object = objects;

	while (object != 0)
	{
		Hit hit;
		object->intersection(ray, hit);
		if (hit.flag)
		{

			if (hit.t < closest.t && hit.t > 0.01)
			{
				closest = hit;
				cout << closest.t << " " << hit.t << endl;

			}

		}
		object = object->next;
	}



	if (closest.flag && closest.t != FLT_MAX)
	{
		colour = closest.what->colour;
		float t = 1 / closest.t;
		t = (t > 255) ? 255 : (t < 0.01) ? 0 : t;
		cout << t << endl;
		colour.x = (colour.x > 255) ? 255 : (colour.x < 0) ? 0 : colour.x;
		colour.y = (colour.y > 255) ? 255 : (colour.y < 0) ? 0 : colour.y;
		colour.z = (colour.x > 255) ? 255 : (colour.z < 0) ? 0 : colour.z;
		cout << "hit " << closest.t << endl;

		vector<float> stuff{ colour.x,colour.y,colour.z, t };
		return stuff;
	}
	//cout << closest.flag << " " << closest.t << endl;
	vector<float> miss{ 0,0,0,0 };
	//cout << "miss" << endl;
	return miss;

}


