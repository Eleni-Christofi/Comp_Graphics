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
  int dir = 1;
  if (sx > ex)
  {
    dir = -1;
  }

  int   x     = sx;
  int y     =  sy;
  int difx = ex - sx;
  int dify = ey - sy;
  int m = dify * dir ;
  float fy = difx / 2;
        
  
  while (x != ex)
  {
    fb->plotPixel(x, y, 1.0f, 1.0f, 1.0f);

    fy += slope;

    x += dir;

	if (fy > difx)
	{
		y += 1;
		fy -= dx;
	}
  }

}

int draw_y_line(FrameBuffer *fb, int sx, int sy, int ex, int ey)
{
  int dir = 1;
  if (sy > ey)
  {
    dir = -1;
  }

  int   x = sx;
  int y = sy;
  int difx = ex - sx;
  int dify = ey - sy;
  int m = difx * dir;
  float fx = dify / 2;
  
  while (y != ey)
  {
    fb->plotPixel(x, y, 1.0f, 1.0f, 1.0f);

    fx += slope;

    y += dir;

	if (fx > dify)
	{
		x += 1;
		fx -= dy;
	}
  }

}


int draw_line(FrameBuffer *fb, int sx, int sy, int ex, int ey)
{
  if ((sx == ex) && (sy==ey))
  {
    return fb->plotPixel(sx, sy, 1.0f, 1.0f, 1.0f);
    
  } else if (((ex-sx)* (ex-sx)) >= ((ey-sy)* (ey-sy)))
  {
    return draw_x_line(fb, sx, sy, ex, ey);
    
  } else
  {
    return draw_y_line(fb, sx, sy, ex, ey);
  }
}
