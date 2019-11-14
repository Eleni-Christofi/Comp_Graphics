
#include <iostream>

#include "framebuffer.h"
#include "camera.h"
#include "scene.h"
#include "transform.h"
#include "object.h"
#include "polymesh.h"
#include "sphere.h"

using namespace std;




int main(int argc, char *argv[])
{
	// Create a framebuffer
	int image_width = 128;
	int image_height = 128;
	FrameBuffer *fb = new FrameBuffer(image_width, image_height);

	//Setting up a camera
	Vector fp = Vector(1,1,-1000);
	float fl = 1.0f;
	Vector look = Vector(2,1,-5) - fp;
	Vector up = Vector(1,2,-5) - fp;
	float ih = 20;
	float iw = 20;
	Camera camera = Camera(fp,fl,look,up,ih,iw,image_height,image_width);

	cout << "camera set up" << endl;

	//Set up the Scene object
	Scene scene = Scene();
	cout << "empty scene set up" << endl;


	//// The following transform allows 4D homogeneous coordinates to be transformed. It moves the supplied teapot model to somewhere visible. (From lab 2)
	//Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 7.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// load in the teapot
	//PolyMesh pm ((char *)"teapot.ply", transform);

	//cout << "teapot loaded" << endl;

	//add teapot to scene 
	//pm.next = scene.objects;
	//scene.objects = &pm;

	//cout << "teapot added to scene" << endl;

	Sphere sphere = Sphere(Vertex(1, 1, 0), 1.0f);
	sphere.colour = Vector(255, 255, 255);
	sphere.next = scene.objects;
	scene.objects = &sphere;
	
	cout << "sphere added" << endl;

	

	//convert image pixel co-ordinates into co-ordinates of the space
	Vector pixel_vec[image_width][image_height];
	for (int i{ 0 }; i < image_width; i++)
	{
		for (int j{ 0 }; j < image_height; j++)
		{
			pixel_vec[i][j] = camera.pixel_coord(i, j);
		}
	}

	cout << "pixel_coords converted" << endl;

	//colours 
	Vector white(255, 255, 255);
	Vector black(0, 0, 0);
	Vector red(255, 0, 0);
	Vector green(0, 255, 0);
	Vector blue(0, 0, 255);


	//raytracing
	Vector ray_direction = Vector();
	Ray ray;
	
	for (int i{ 0 }; i < image_width; i++)
	{
		for (int j{ 0 }; j < image_height; j++)
		{

			ray_direction = pixel_vec[i][j] - camera.focal_p;
			ray = Ray(camera.focal_p, ray_direction);
			Vector colour = scene.get_pixel_colour(ray);
			fb->plotPixel(i, j, colour.x, colour.y, colour.z);
			
		

		}
	}
	fb->writeRGBFile((char *)"test.ppm");
}



//const Sphere light(Vector(0, 0, 50), 1);
//Vector L = light.c - hit.position;
//L = L.normalise();
//Vector N = hit.normal;
//N = N.normalise();
//float dt = L.dot(N);
//hit.colour = white * dt;
//clamp255(hit.colour);