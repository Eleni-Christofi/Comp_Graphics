#pragma once

#include "vector.h"
#include "transform.h"
#include "object.h"


class Plane : public Object {
public:
	Vector normal; // n in x*n = d
	float d; // d in x*n = d

	//given normal and a point, assign n and d 
	Plane(Vector n, Vector x)
	{
		normal = n;
		d = n.dot(x);
	}

	Plane(Vector n, float D)
	{
		normal = n;
		d = D;
	}

	void intersection(Ray ray, Hit &hit)
	{
		//if the ray and plane are parallel, no intersection
		if (fabs(normal.dot(ray.direction)) <= 0.00000001) { hit.flag = false; }

		//if the object is backwards facing, we don't want to show it
		if (normal.dot(ray.direction) > 0) normal.negate();

		//find t in ray equation p + td
		float t = -(normal.dot(ray.position) - d) / normal.dot(ray.direction);

		//check if triangle is behind ray
		if (t < 0) { hit.flag = false; }


		//define plane intersection location
		Vector phit = ray.position + (ray.direction)*t;

		hit.flag = true;
		hit.t = t;
		hit.what = this;
		hit.position = phit;
		hit.normal = normal;
		hit.normal.normalise();
	}
};



