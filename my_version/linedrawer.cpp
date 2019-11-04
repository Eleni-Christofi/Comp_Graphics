 /***************************************************************************
 *
 * krt - Kens Raytracer - Coursework Edition. (C) Copyright 1997-2019.
 *
 * Do what you like with this code as long as you retain this comment.
 */

/* This is the code you will need to replace for Lab 1.
 *
 * It contains two simple implementations that loop over the longest axis adding the gradient to the position on the other axis at each step.
 * The objective is for you to remove the use of floating point variables and work entirely with integers.
 * You should use Bresenhams Line Algorithm to achieve this.
 */

#include <iostream>
#include "linedrawer.h"

int draw_x_line(FrameBuffer *fb, int sx, int sy, int ex, int ey)
{

	int y = sy;
	int x = sx;
	int dy = ey - sy;
	int dx = ex - sx;
	
	int dir = 1;
	if (dy < 0)
	{
		dir = -1;
		dy = -dy;
	}

	int p = 2 * dy - dx;

	while (x <= ex)
	{
		fb->plotPixel(x, y, 1.0f, 1.0f, 1.0f);
		if (p < 0)
		{
			x += 1;
			p += 2 * dy;
		}
		else
		{
			x += 1;
			y += dir;
			p += 2 * (dy - dx);
		}

	}

}

int draw_y_line(FrameBuffer *fb, int sx, int sy, int ex, int ey)
{

	
	int y = sy;
	int x = sx;
	int dy = ey - sy;
	int dx = ex - sx;
	
	int dir = 1;
	if (dx < 0)
	{
		dir = -1;
		dx = -dx;
	}

	int p = 2 * dx - dy;

	while (y <= ey)
	{
		fb->plotPixel(x, y, 1.0f, 1.0f, 1.0f);
		if (p < 0)
		{
			y += 1;
			p += 2 * dx;
		}
		else
		{
			y += 1;
			x += dir;
			p += 2 * (dx - dy);
		}

	}

}


int draw_line(FrameBuffer *fb, int sx, int sy, int ex, int ey)
{
  if ((sx == ex) && (sy==ey))
  {
    return fb->plotPixel(sx, sy, 1.0f, 1.0f, 1.0f);
    
  } 
  else if (((ex-sx)* (ex-sx)) >= ((ey-sy)* (ey-sy)))
  {
	  if (sx > ex)
	  {
		  return draw_x_line(fb, ex, ey, sx, sy);
	  }
	  else
	  {
		  return draw_x_line(fb, sx, sy, ex, ey);
		  
	  }
    
    
  } 
  else
  {
	  if (sy > ey)
	  {
		  return draw_y_line(fb, ex, ey, sx, sy);
	  }
	  else
	  {
		  return draw_y_line(fb, sx, sy, ex, ey);
	  }
  }
}
