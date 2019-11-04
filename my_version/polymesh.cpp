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
		cout << vertex_count <<endl;
		triangle_count = f;
		cout << triangle_count <<endl;
	}

	vertex = new Vertex[vertex_count];
	triangle = new TriangleIndex[triangle_count];

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
			triangle[i][0] = p - 1;
			triangle[i][1] = q - 1;
			triangle[i][2] = r - 1;
		}

		

	}

}


