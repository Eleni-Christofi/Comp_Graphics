/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#pragma once

#include "vertex.h"
#include "object.h"

class Sphere : public Object {
	Vertex centre;
	float  radius;
public:
	Sphere(Vertex c, float r) 
	{
		centre = c; 
		radius = r;
	}
	
	Vector get_norm(const Vector& pi) const { return (pi - c) / r; }

	void intersection(Ray ray, Hit &hit);
	{
		const Vector p = ray.position;
		const Vector d = ray.direction;
		const Vector pc = p - Vector(c.x,c.y,c.z);
		
		const double b = 2 * pc.dot(d);
		const double c = pc.dot(pc) - r * r;
		
		double disc = b * b - 4 * c;
		if (disc < 1e-4) hit.flag = false;
		
		disc = sqrt(disc);
		
		const double t0 = -b - disc;
		const double t1 = -b + disc;
		hit.t = (t0 < t1) ? t0 : t1;
		hit.flag = true;
		
		Vector pi = p = d * t;
		hit.position = pi;
		hit.normal = get_norm(pi);

	}
};
