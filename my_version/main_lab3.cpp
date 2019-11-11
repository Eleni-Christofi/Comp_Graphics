
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
	Camera camera = Camera();

	//Set up the Scene object
	Scene scene;


	//// The following transform allows 4D homogeneous coordinates to be transformed. It moves the supplied teapot model to somewhere visible. (From lab 2)
	Transform *transform = new Transform(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 7.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	// load in the teapot
	PolyMesh pm ((char *)"teapot.ply", transform);

	//add teapot to scene 
	scene.objects.push_back(pm);

	

	//convert image pixel co-ordinates into co-ordinates of the space
	Vector pixel_vec[image_width][image_height];
	for (int i{ 0 }; i < image_width; i++)
	{
		for (int j{ 0 }; j < image_height; j++)
		{
			pixel_vec[i][j] = camera.pixel_coord(i, j);
		}
	}

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
			float d = scene.get_pixel_depth(ray);
			fb->plotDepth(i, j, d);
			
		

		}
	}
	fb->writeDepthFile((char *)"test.ppm");
}



//const Sphere light(Vector(0, 0, 50), 1);
//Vector L = light.c - hit.position;
//L = L.normalise();
//Vector N = hit.normal;
//N = N.normalise();
//float dt = L.dot(N);
//hit.colour = white * dt;
//clamp255(hit.colour);
//fb->plotPixel(i, j, hit.colour.x, hit.colour.y, hit.colour.z);