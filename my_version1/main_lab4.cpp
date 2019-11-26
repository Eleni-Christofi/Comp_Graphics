
#include <iostream>

#include "framebuffer.h"
#include "camera.h"
#include "scene.h"
#include "transform.h"
#include "object.h"
#include "polymesh.h"
#include "sphere.h"
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
	Scene scene = Scene();
	cout << "empty scene set up" << endl;

	//Put some lights in
	Vector colour = Vector(1, 1, 1);
	float intensity = 1;
	Vector p1 = Vector(1, 1, 0);
	PointLight* l1 = new PointLight(colour, intensity, p1);
	scene.lights.push_back(l1);

	// The following transform allows 4D homogeneous coordinates to be transformed. It moves the supplied teapot model to somewhere visible. (From lab 2)
	Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 7.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// load in the teapot
	PolyMesh pm ((char *)"teapot.ply", transform);
	pm.colour = Vector(255, 0, 0);

	cout << "teapot loaded" << endl;

	//add teapot to scene
	//pm.next = scene.objects;
	//scene.objects = &pm;

	cout << "teapot added to scene" << endl;
	

	Sphere sphere = Sphere(Vertex(0, 0, 215), 200);
	sphere.colour = Vector(255, 255, 255);
	sphere.next = &pm;
	scene.objects = &sphere;

	cout << "sphere added" << endl;

	




	//raytracing
	Vector ray_direction = Vector();
	Ray ray;

	for (int i{ 0 }; i < pixel_width + 1; i++)
	{
		for (int j{ 0 }; j < pixel_height + 1; j++)
		{
			vector<float> pixel_info;
			//cout << "made pixel info" << endl;
			ray = camera.make_ray(i, j);
			//cout << "gotten ray" << endl;
			pixel_info = scene.get_pixel(ray);
			//cout << "got pixel info" << endl;
			fb->plotPixel(i, j, pixel_info[0], pixel_info[1], pixel_info[2]);
			//fb->plotDepth(i, j, pixel_info[3]);

			//cout << pixel_info[0] << pixel_info[1] << pixel_info[2] << endl;



		}
	}
	cout << "Writing files..." << endl;
	fb->writeRGBFile((char *)"test.ppm");

}



