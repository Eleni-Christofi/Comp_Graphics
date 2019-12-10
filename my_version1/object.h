/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

// Object is the base class for objects.
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ray.h"
#include "hit.h"

class Object {
public:

	Object *next;
	Vector colour;
	float kd; //diffuse
	float ks; //specular
	float kr; //reflection
	float ri; //refractive index
	int type; // 0 = diffuse & specular, 1 = add reflection, 2= reflect and refract

	Object()
	{
		next = (Object *)0;
		colour = Vector(255, 255, 255);
		kd = 0.5;
		ks = 0.8;
		kr = 0.6;
		ri = 0.33;
	}

	Object(Vector col, float d, float s, float r, float i, int ty)
	{
		next = (Object *)0;
		colour = col;
		kd = d;
		ks = s;
		kr = r;
		ri = i;
		type = ty;
	}
	
	virtual void intersection(Ray ray, Hit &hit)
	{

	}

	int get_type()
	{
		return type;
	}
};

#endif
