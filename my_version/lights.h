#pragma once
#include "vector.h"
#include "transform.h"


class Light
{
public:
	virtual ~Light() {}
	Vector colour;
	float intensity;
	virtual Vector get_direction(Vector &p){}

};

class PointLight : public Light
{
public:
	Vector position;

	PointLight(Vector c, float i, Vector p)
	{
		this->colour = c;
		this->intensity = i;
		this->position = p;
	}

	Vector get_direction(Vector &p) 
	{
		Vector d = position - p;
		d.normalise();

		return d;
	}

	Vector get_intensity(Vector &p)
	{
		float len = (position - p).norm();
		Vector lightint = colour * intensity/ (4 * M_PI*len);
		return lightint;
	}
};

class DistantLight : public Light
{
public:
	Vector direction;

	DistantLight(Vector c, float i, Vector d)
	{
		this->colour = c;
		this->intensity = i;
		d.normalise();
		this->direction = d;
	}

	Vector get_direction(Vector &p)
	{
		return direction;
	}
};