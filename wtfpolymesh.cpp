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
#include <vector>

using namespace std;

class Point_3D
{
	float x_value, y_value, z_value;

public:
	void set_values(float, float, float);
	float TakeXValue(Point) { return x_value };
	float TakeYValue(Point) { return y_value };
	float TakeZValue(Point) { return z_value };
		
};

void set_values(float x, float y, float z)
{
	x_value = x;
	y_value = y;
	z_value = z;
}


class TriangleIndex
{
	Point_3D v1, v2, v3;


};

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
	
}


int main() {

	//initialising variables
	string myString;
	float aNumber;
	vector<Point_3D> vert;

    //open the file
	ifstream myfile("teapot.ply");
   ofstream output;
   
   //if the file isn't open, return an error
	if (!myfile.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}

	//while I haven't reached the end of the file
	while (!myfile.eof())
	{   //get the line from the file
		do
		{
			getline(myfile, myString);
		}
		//if the current line doesn't say end_header
		while (myString != "end_header")
		{
			getline(myfile, myString);
			myfile >> aNumber;
			output << aNumber;


			
		}
		
	}
		return 0;
}


//vert.push_back(aNumber); is what I want to use 

// what I wanna do: 
// read the ply file
// take all the vertices and convert them into Point_3D class objects and store them in an array
// take the faces and find the relevant Point objects (store as triangles)
// get main lab 2 to plot the triangles
