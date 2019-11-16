#include "vector.h"
#include "vertex.h"
#include "ray.h"
#include <iostream>

using namespace std;

struct Camera
{
public:
	Vector focal_p;
	float focal_length;
	Vector w; //look direction
	Vector v; //taken from up direction
	Vector u;  
	float image_h;
	float image_w;
	float reso_h;
	float reso_w;
	float pixel_h;
	float pixel_w;
	Vector top_left;

	//constructor
	Camera(Vector fp, float fl, Vector look, Vector up, float ih, float iw, float rh, float rw)
	{
		look.negate();
		focal_p = fp;
		focal_length = fl;
		w = look;
		u = w.cross(up,u);
		v = u.cross(w,v);
		image_h = ih;
		image_w = iw;
		reso_h = rh;
		reso_w = rw;
		pixel_h = ih / rh;
		pixel_w = iw / rw;

		top_left = fp + (w*fl) - (u*(iw / 2)) + (v*(ih / 2));
	}

	//deconstructor 
	~Camera() {};

	//method to calculate ray to pixel (i,j) from camera 
	Ray make_ray(int i, int j)
	{
		Vector point = top_left + (u*i*pixel_w) - (v*j*pixel_h);
		//cout << "Top Left" << top_left.x << " " << top_left.y << " " << top_left.z << endl;
		//cout << "i: " << i << " j: " << j << endl;
		//cout << "Point" << point.x << " " << point.y << " " << point.z << endl;
		//cout << endl;
		Vector dir = point - focal_p;
		dir.normalise();
		return Ray(focal_p, dir);
	}

};