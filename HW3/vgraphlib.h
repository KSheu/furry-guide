//
// CS31 Winter 2015
// File: HW #3-Vintage Graphics_vgraphlib Header File
// Author: Katherine Sheu (katherinesheu@ucla.edu)
// SID: 304150980
// Date: 2015-1-30
// Version: 1.0
// Description: Software for vintage graphics using ASCII characters
//				User inputs: canvas_size, pen, shape, shape type, height, width
//				Output: geometric shapes using ASCII chracters


#ifndef _VGRAPHLIB_H
#define _VGRAPHLIB_H
//
// Global Constants
//
const int CANVAS_HEIGHT = 40;
const int CANVAS_WIDTH = 50;
//
// Functional Prototypes
//
bool cmd_canvas_setup(int & height, int & width);
bool cmd_pen_selection(char & pen);
bool cmd_draw_vertical_line(char pen, int height);
bool cmd_draw_horizontal_line(char pen, int width);
bool cmd_draw_rectangle(char pen, char type, int height, int width);
bool cmd_draw_right_triangle(char pen, char type, int width);

//bool input_shape_type(char&type);
bool input_shape_height(int&height);
bool input_shape_width(int&width);
//bool input_triangle_width(int&width, int&height);

#endif // _VGRAPHLIB_H