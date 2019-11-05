
#include <iostream>

#include "framebuffer.h"
#include "object.h"
#include "camera.h"
#include "polymesh.h"

using namespace std;




int main(int argc, char *argv[])
{
	// Create a framebuffer
	int image_width = 128;
	int image_height = 128;
	FrameBuffer *fb = new FrameBuffer(image_width, image_height);

	//Setting up a camera
	camera = Camera();


	//// The following transform allows 4D homogeneous coordinates to be transformed. It moves the supplied teapot model to somewhere visible. (From lab 2)
	//Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 7.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// load in the teapot
	//PolyMesh *pm = new PolyMesh((char *)"teapot.ply", transform);

	//put a sphere in
	const Sphere sphere(Vector(image_width*0.5, image_height*0.5, 50), 50);
	const Sphere light(Vector(0, 0, 50), 1);

	//convert image pixel co-ordinates into co-ordinates of the space
	pixel_vec[image_width][image_height];
	for (int i{ 0 }; i < image_width; i++)
	{
		for (int j{ 0 }; j < image_height; j++)
		{
			pixel_vec[i][j] = camera.pixel_coord(i, j);
		}
	}

	//colours 
	const Vector white(255, 255, 255);
	const Vector black(0, 0, 0);
	const Vector red(255, 0, 0);
	const Vector green(0, 255, 0);
	const Vector blue(0, 0, 255);


	//raytracing
	Vector ray_direction = Vector();
	Ray ray;
	Vector pixel_col{ black };
	
	for (int i{ 0 }; i < image_width; i++)
	{
		for (int j{ 0 }; j < image_height; j++)
		{
			pixel_col = black;
			ray_direction = pixel_vec[i][j] - camera.focal_p;
			ray = Ray(camera.focal_point, ray_direction);
			double t = numeric_limits<double>::infinity();
			Hit hit;
			sphere.intersect(ray, hit);
			if (hit.flag)
			{
				Vector L = light.c - hit.position;
				L = L.normalize();
				Vector N = sphere.get_norm(pi);
				N = N.normalize();
				const double dt = L.dot(N);
				pixel_col = white * dt;
				clamp255(pixel_col);
			}
		

		}
	}

}

void clamp255(Vector& colour)
{
	colour.x = (colour.x > 255) ? 255 : (colour.x < 0) ? 0 : colour.x;
	colour.y = (colour.y > 255) ? 255 : (colour.y < 0) ? 0 : colour.y;
	colour.z = (colour.x > 255) ? 255 : (colour.z < 0) ? 0 : colour.z;
}
