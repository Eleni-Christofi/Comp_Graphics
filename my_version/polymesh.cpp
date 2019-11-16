/***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "polymesh.h"
#include <float.h>

using namespace std;

PolyMesh::PolyMesh(char *file)
{
	Transform *transform = new Transform();

	this->do_construct(file, transform);
}

PolyMesh::PolyMesh(char *file, Transform *transform)
{
	this->do_construct(file, transform);
}

void PolyMesh::do_construct(char *file, Transform *transform)
{

	//open the file
	ifstream myfile("teapot.ply");

	//if the file isn't open, return an error
	if (!myfile.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}

	myfile.ignore('\n');
	string a, b, d, e;
	int c, f;

	if (myfile >> a >> b >> c >> d >> e >> f)
	{
		vertex_count = c;
		triangle_count = f;
	}

	vertex = new Vertex[vertex_count];
	triangleV = new TriangleIndex[triangle_count];

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	//loop to process vertices into vectors 
	
	for (int i = 0; i < vertex_count; i++)
	{
		
		if (myfile >> x >> y >> z)
		{
			vertex[i].x = x;
			vertex[i].y = y;
			vertex[i].z = z;

			transform->apply(vertex[i]);
		}

		
	}
	
	int k = 0;
	int p = 0;
	int q = 0;
	int r = 0;
	
	//loop to process faces into triangles
	for (int i = 0; i < triangle_count; i++)
	{
	
		if (myfile>>k >> p >> q >> r)
		{
			triangleV[i][0] = p - 1;
			triangleV[i][1] = q - 1;
			triangleV[i][2] = r - 1;
		}

		

	}

}

void PolyMesh::intersection(Ray ray, Hit &hit)
{
	//for each triangle in the mesh
	for (int i{ 0 }; i < triangle_count; i++)
	{
		Vector v0, v1, v2;

		//triangle vertices
		 v0.x = vertex[triangleV[i][0]].x;
		 v0.y = vertex[triangleV[i][0]].y;
		 v0.z = vertex[triangleV[i][0]].z;
		 
		 v1.x = vertex[triangleV[i][1]].x;
		 v1.y = vertex[triangleV[i][1]].y;
		 v1.z = vertex[triangleV[i][1]].z;
		 
		 v2.x = vertex[triangleV[i][2]].x;
		 v2.y = vertex[triangleV[i][2]].y;
		 v2.z = vertex[triangleV[i][2]].z;

		//set up plane for triangle
		Vector AB =  v1 - v0;
		Vector AC = v2 - v0;
		Vector tnorm = AB.cross(AC, tnorm);
		tnorm.normalise();
		float D = AB.dot(tnorm);

		//if the ray and plane are parallel, no intersection
		if (tnorm.dot(ray.direction) == 0) continue;

		//if the object is backwards facing, we don't want to show it
		if (tnorm.dot(ray.direction) > 0) tnorm.negate();
		
		//find t in ray equation p + td
		float t = -(tnorm.dot(ray.position) + D) / tnorm.dot(ray.direction);

		//check if triangle is behind ray
		if (t < 0) continue;


		//define plane intersection location
		Vector phit = ray.position + (ray.direction)*t;

		//is p inside triangle boundary
		Vector edge0 = v1 - v0;
		Vector edge1 = v2 - v1;
		Vector edge2 = v0 - v2;
		Vector c0 = phit - v0;
		Vector c1 = phit - v1;
		Vector c2 = phit - v2;
		Vector r0 = edge0.cross(c0, r0);
		Vector r1 = edge1.cross(c1, r1);
		Vector r2 = edge2.cross(c2, r2);
		
		if (tnorm.dot(r0) > 0 && tnorm.dot(r1) > 0 && tnorm.dot(r2) > 0)
		{
			hit.flag = true;
			hit.t = t;
			hit.position = phit;
			hit.normal = tnorm;
			break;
		}
		


	}
}