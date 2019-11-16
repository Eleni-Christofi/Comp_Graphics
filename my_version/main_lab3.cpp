
#include <iostream>

#include "framebuffer.h"
#include "camera.h"
#include "scene.h"
#include "transform.h"
#include "object.h"
#include "polymesh.h"
#include "sphere.h"
#include <float.h>

using namespace std;




int main(int argc, char *argv[])
{
	// Create a framebuffer
	int image_width = 128;
	int image_height = 128;
	FrameBuffer *fb = new FrameBuffer(image_width, image_height);

	//Setting up a camera
	Vector fp = Vector(0,0,-10);
	float fl = 10.0f;
	Vector look = Vector(0, 0, 1);
	Vector up = Vector(0, 1, 0);
	float ih = 10;
	float iw = 10;
	Camera camera = Camera(fp,fl,look,up,ih,iw,image_height,image_width);

	cout << "camera set up" << endl;

	//Set up the Scene object
	Scene scene = Scene();
	cout << "empty scene set up" << endl;


	//// The following transform allows 4D homogeneous coordinates to be transformed. It moves the supplied teapot model to somewhere visible. (From lab 2)
	//Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 7.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// load in the teapot
	PolyMesh pm ((char *)"teapot.ply");
	pm.colour = Vector(255, 0, 0);

	cout << "teapot loaded" << endl;

	//add teapot to scene 
	pm.next = scene.objects;
	scene.objects = &pm;

	cout << "teapot added to scene" << endl;

	
	/**Sphere sphere = Sphere(Vertex(1, 1, 0), 1.0f);
	sphere.colour = Vector(255, 255, 255);
	sphere.next = scene.objects;
	scene.objects = &sphere;
	
	cout << "sphere added" << endl;
	*/
	

	

	//raytracing
	Vector ray_direction = Vector();
	Ray ray;
	
	for (int i{ 0 }; i < image_width + 1; i++)
	{
		for (int j{ 0 }; j < image_height + 1; j++)
		{
			vector<float> pixel_info;
			ray = camera.make_ray(i, j);
			pixel_info = scene.get_pixel(ray);
			fb->plotPixel(i, j, pixel_info[0], pixel_info[1] , pixel_info[2]);
			fb->plotDepth(i, j, pixel_info[3]);

			
		

		}
	}
	fb->writeRGBFile((char *)"test.ppm");
}


