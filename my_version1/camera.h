#include "vector.h"
#include "vertex.h"
#include "ray.h"
#include "scene.h"
#include <iostream>

using namespace std;

struct Camera
{
public:
	Vector camera_pos;
	float image_dist;
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

	//parameters for adding depth of field
	float focal_length;
	float aperture_size;

	//constructor
	Camera(Vector cp, float id, Vector look, Vector up, float ih, float iw, float rh, float rw)
	{
		look.negate();
		camera_pos = cp;
		image_dist = id;
		w = camera_pos - look;
		w.normalise();
		u = w.cross(up, u);
		u.normalise();
		v = u.cross(w, v);
		v.normalise();
		image_h = ih;
		image_w = iw;
		reso_h = rh;
		reso_w = rw;
		pixel_h = ih / rh;
		pixel_w = iw / rw;

		top_left = cp + (w*id) - (u*(iw / 2)) + (v*(ih / 2));
	}

	//deconstructor
	~Camera() {};

	//method to calculate ray to pixel (i,j) from camera 
	Ray make_ray(int i, int j)
	{
		//cout << "i: " << i << " j: " << j << endl;
		Vector point = top_left + (u*i*pixel_w) - (v*j*pixel_h);
		Vector dir = point - camera_pos;
		dir.normalise();
		return Ray(camera_pos, dir);
	};

	Vector DoF(Scene scene, Ray ray, float depth)
	{
		int n = floor(depth*100);
		Vector blend = Vector();

		for (int i = 0; i < n; i++)
		{
			float u = -0.5 + (((float)rand()) / (float)RAND_MAX);
			u *= aperture_size;
			float v = -0.5 + (((float)rand()) / (float)RAND_MAX);
			v *= aperture_size;
			float w = -0.5 + (((float)rand()) / (float)RAND_MAX);
			w *= aperture_size;
			//cout << "uvw: " << u << " " << v << " " << w << endl;
			
			Vector P = ray.position + ray.direction * focal_length;
			Vector pos = Vector();
			pos.x = ray.position.x + u; //cout << pos.x << endl;
			pos.y = ray.position.y + v; //cout << pos.y << endl;
			pos.z = ray.position.z + w; //cout << pos.z << endl;

			Vector dir = P - pos;
			dir.normalise();
			Ray new_ray = Ray(pos, dir);
		

			vector<float> pixel_info = scene.get_pixel(new_ray, 1);
			Vector colour = Vector(pixel_info[0], pixel_info[1], pixel_info[2]);
			//cout << "colour: " << colour.x << " " << colour.y << " " << colour.z << endl;
			blend = blend + colour;
			//cout << "n: " << n << " blend: " << blend.x << " " << blend.y << " " << blend.z << endl;
		}
		blend = blend / n;
		return blend;
	};

};