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
	int pixel_width = 256;
	int pixel_height = 256;
	FrameBuffer *fb = new FrameBuffer(pixel_width, pixel_height);

	//Setting up a camera
	Vector fp = Vector(0, 0, 0);
	float fl = 1.0f;
	Vector look = Vector(0, 0, 1);
	Vector up = Vector(0, 1, 0);
	float ih = 2;
	float iw = 2;
	Camera camera = Camera(fp, fl, look, up, ih, iw, pixel_height, pixel_width);

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

	// The following transform allows 4D homogeneous coordinates to be transformed. It moves the supplied teapot model to somewhere visible. (From lab 2)
	Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 11.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// load in the teapot
	PolyMesh pm((char *)"teapot_smaller.ply", transform);
	pm.colour = Vector(255, 0, 255);
	pm.type = 0;
	pm.kr = 1;

	//cout << "teapot added to scene" << endl;
	/*
	Sphere sphere3 = Sphere(Vertex(-3, 0, 3), 1);
	sphere3.colour = Vector(50, 50, 50);
	sphere3.type = 1;
	sphere3.kr = 1;



	Sphere sphere = Sphere(Vertex(0, 3, 3), 1);
	sphere.colour = Vector(50, 50, 50);
	sphere.type = 1;
	sphere.kr = 1;
	sphere.next = &sphere3;`
	scene.objects = &sphere;

	*/




	cout << "sphere added" << endl;

	//add plane as the 'floor'
	/*Plane floor = Plane(Vector(0, 1, 0), Vector(0, -5, 0));
	floor.colour = Vector(100, 0, 0);
	floor.type = 0;
	floor.kr = 1;
	pm.next = &floor;

	cout << "floor added" << endl;

	*/

	//add lots of spheres as backdrop
	Sphere b1 = Sphere(Vertex(0, 0, 1.5), 1);
	b1.colour = Vector();
	b1.type = 2;
	b1.ri = 1.517;
	b1.kt = 0.5;
	b1.kr = 0.05;
	b1.next = &pm;
	scene.objects = &b1;








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
			Vector colour = Vector(pixel_info[0], pixel_info[1], pixel_info[2]);

			fb->plotPixel(i, j, colour.x, colour.y, colour.z);



		}
	}
	cout << "Writing files..." << endl;
	fb->writeRGBFile((char *)"test.ppm");

}

