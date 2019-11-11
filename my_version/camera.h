#include "vector.h"
#include "vertex.h"

struct Camera
{
	Vector focal_p;
	float focal_length;
	Vector forward_dir;
	Vector up_dir;
	Vector right_dir;
	float image_h;
	float image_w;
	float reso_h;
	float reso_w;
	float pixel_h;
	float pixel_w;

	Camera()
	{
		focal_p = Vector();
		focal_length = 1.0f;
		forward_dir = Vector(0, 0, 1);
		up_dir = Vector(0, 1, 0);
		right_dir = Vector(1, 0, 0);
		image_h = 100;
		image_w = 100;
		reso_h = 128;
		reso_w = 128;
		pixel_h = image_h / reso_h;
		pixel_w = image_w / reso_w;

	}

	Camera(Vector fp, float fl, Vector fd, Vector ud, Vector rd, float ih, float iw, float rh, float rw)
	{
		focal_p = fp;
		focal_length = fl;
		forward_dir = fd;
		up_dir = ud;
		right_dir = rd;
		image_h = ih;
		image_w = iw;
		reso_h = rh;
		reso_w = rw;
		pixel_h = ih / rh;
		pixel_w = iw / rw;
	}

	Vector pixel_coord(int i, int j)
	{
		float r = 0.5 - (((0.5 + j) / reso_w)*image_w);
		float b = 0.5 - (((0.5 + i) / reso_h)*image_h);

		return (focal_p + (forward_dir * (focal_length)) + (up_dir * (b)) + (right_dir * (r)));
	}

};