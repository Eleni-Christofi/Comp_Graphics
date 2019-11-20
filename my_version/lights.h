#pragma once
#include "vector.h"
#include "transform.h"


class Light
{
public:
	Light(const Transform &l2w) : lightToWorld(l2w) {}
	virtual ~Light() {}
	Matrix44f lightToWorld;
	Vector colour;
	float intensity
};

class PointLight : public Light
{
public:
	Vector position;

	PointLight(const Transform &l2w, const Vector &c = Vector(1, 1, 1), const float &i = 1) : Light(l2w)
	{
		this->colour = c;
		this->intensity = i;
		l2w.apply(Vector(0, 0, 0), position);
	}

	Vector get_shading(Vector &p, Vector &lightdir, Vector &lightint, float &distance) 
	{
		lightdir = position - p;
		float len = lightdir.norm();
		distance = sqrt(len);
		lightdir.normalise();
		lightint = intensity * colour / (4 * M_PI*len);
	}
};

class DistantLight : public Light
{
public:
	Vector direction;

	DistantLight(const Transform &l2w, const Vector &c = Vector(1, 1, 1), const float &i = 1) : Light(l2w)
	{
		this->colour = c;
		this->intensity = i;
		l2w.apply(Vector(0, 0, 0), direction);
		direction.normalise();
	}
};