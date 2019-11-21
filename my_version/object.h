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
	float kd;
	float ks;

	Object()
	{
		next = (Object *)0;
		colour = Vector(255, 255, 255);
		kd = 0.5;
		ks = 0.8;
	}
	
	virtual void intersection(Ray ray, Hit &hit)
	{

	}
};

#endif
