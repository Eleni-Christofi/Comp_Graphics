#include <iostream>

#include "framebuffer.h"
#include "camera.h"
#include "scene.h"
#include "transform.h"
#include "object.h"
#include "polymesh.h"
#include "sphere.h"
#include "plane.h"
#include <float.h>
#include <vector>

using namespace std;




int main(int argc, char *argv[])
{
	// Create a framebuffer
	int pixel_width = 1024;
	int pixel_height = 1024;
	FrameBuffer *fb = new FrameBuffer(pixel_width, pixel_height);

	//Setting up a camera
	Vector cp = Vector(0, 0, 0);
	float id = 1.0f;
	Vector look = Vector(0, 0, 1);
	Vector up = Vector(0, 1, 0);
	float ih = 2;
	float iw = 2;
	Camera camera = Camera(cp, id, look, up, ih, iw, pixel_height, pixel_width);

	camera.focal_length = 3;
	camera.aperture_size = 0.5;

	cout << "camera set up" << endl;

	//Set up the Scene object
	Scene scene = Scene(Vector(175, 175, 175), 0.3, 2);
	cout << "empty scene set up" << endl;

	//Put some lights in
	Vector colour = Vector(1, 1, 1);
	float intensity = 1;
	Vector p1 = Vector(1, 1, 0);

	PointLight* l1 = new PointLight(colour, intensity, p1);
	scene.lights.push_back(l1);

	
	Sphere sphere3 = Sphere(Vertex(1, 0, 10), 2);
	sphere3.colour = Vector(255, 125, 0);
	sphere3.type = 0;
	sphere3.kr = 1;


	Sphere sphere = Sphere(Vertex(-2, 0, 5), 2);
	sphere.colour = Vector(255, 20, 20);
	sphere.type = 0;
	sphere.kr = 1;
	sphere.next = &sphere3;
	scene.objects = &sphere;
	
	Sphere b1 = Sphere(Vertex(6, 0, 20), 2);
	b1.colour = Vector(255, 255, 0);
	b1.type = 0;
	b1.kr = 0.2;
	sphere3.next = &b1;

	Sphere b2 = Sphere(Vertex(-3, 0, 2), 2);
	b2.colour = Vector(255, 0, 0);
	b2.type = 0;
	b2.kr = 0.2;
	b1.next = &b2;

	Sphere b3 = Sphere(Vertex(13, 0, 25), 2);
	b3.colour = Vector(0, 255, 0);
	b3.type = 0;
	b3.kr = 0.2;
	b2.next = &b3;






	//raytracing
	Vector ray_direction = Vector();
	Ray ray;

	for (int i{ 0 }; i < pixel_width + 1; i++)
	{
		for (int j{ 0 }; j < pixel_height + 1; j++)
		{
			vector<float> pixel_info;

			ray = camera.make_ray(i, j);
			pixel_info = scene.get_pixel(ray, 1);
			Vector colour = Vector();
			colour = camera.DoF(scene, ray, pixel_info[3]);
			//colour.x += pixel_info[0];
			//colour.y += pixel_info[1];
			//colour.z += pixel_info[2];
			fb->plotPixel(i, j, colour.x, colour.y, colour.z);



		}
	}
	cout << "Writing files..." << endl;
	fb->writeRGBFile((char *)"test.ppm");

}



