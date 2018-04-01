//
// CS31 Winter 2015
// File: HW #3-Vintage Graphics_vgraphlib
// Author: Katherine Sheu (katherinesheu@ucla.edu)
// SID: 304150980
// Date: 2015-1-30
// Version: 1.0
// Description: Software for vintage graphics using ASCII characters
//				User inputs: canvas_size, pen, shape, shape type, height, width
//				Output: geometric shapes using ASCII chracters



#include<iostream>
#include<string>
#include "vgraphlib.h"
using namespace std;

const string INPUT_SHAPE_HEIGHT = "Input the height: ";
const string INPUT_SHAPE_WIDTH = "Input the width: ";

//the shape sizes which are initialized with user input
int vertical_height;
int horiz_width;

//Asks and validates user inputed canvas size
bool cmd_canvas_setup(int & height, int & width){
	cout << "Input the canvas height you'd like to use: ";
	cin >> height;
	if (!((height > 0) && (height <= CANVAS_HEIGHT))){
		cout << "Height must be between 0 and " << CANVAS_HEIGHT << endl;
		return false;
		//cin >> pic_h;
	}
	//make sure height is right before ever asking for the width
	cout << "Input the canvas width you'd like to use: ";
	cin >> width;
	if (!((width > 0) && (width <= CANVAS_WIDTH))){
		cout << "Width must be between 0 and " << CANVAS_WIDTH << endl;
		return false;
		//cin >> pic_w;
	}
	return true;
}

//Asks and validates pen selection as an ASCII character
bool cmd_pen_selection(char & pen){
	cout << "Input the character you'd like to use: ";
	cin >> pen;
	//Returns true if it is an ASCII character
	if (isprint(pen) == false)
	{
		cout << "Pen must be a printable character.\n";
		return false;
	}
	//ignore anything left over in the stream
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return true;
}
//Draws vertical lines of specified height, 0 height prints nothing
bool cmd_draw_vertical_line(char pen, int height){
	input_shape_height(height);
	for (int i = 0; i < vertical_height; i++){
		cout << pen << endl;
	}
	return true;

}

//Draws horizontal lines of specified width, 0 width prints empty line 
bool cmd_draw_horizontal_line(char pen, int width)
{
	input_shape_width(width);
	for (int i = 0; i <horiz_width; i++){
		cout << pen;
	}
	cout << endl;
	return true;
}

//Function that draws the rectangles
bool cmd_draw_rectangle(char pen, char type, int height, int width){
	//Check height and width
	input_shape_height(height);
	input_shape_width(width);

	if ((type == 's') || (type == 'S')){
		for (int i = 0; i < vertical_height; i++){
			for (int j = 0; j < horiz_width; j++){
				cout << pen;
			}
			cout << endl;
		}
	}
	//Draws the hollow shapes using if statements within for loops
	if ((type == 'h') || (type == 'H'))
	{
		for (int i = 0; i < vertical_height; i++)
		{
			for (int j = 0; j < horiz_width; j++)
			{
				//Draws bottom and top edges
				if ((i == 0) || (i == vertical_height - 1))
				{
					cout << pen;
				}
				//Draws the side edges
				else if ((j == 0) || (j == horiz_width - 1))
				{
					cout << pen;
				}
				//Draws empty spaces for the middle
				else
					cout << " ";
			}
			cout << endl;
		}
	}
	return true;

}

//Function that draws the right triangle
bool cmd_draw_right_triangle(char pen, char type, int width){
	
	input_shape_width(width);

	if ((type == 's') || (type == 'S')){
		for (int i = 0; i < horiz_width; i++){
			for (int j = 0; j <= i; j++){
				cout << pen;
			}
			cout << endl;
		}
	}
	//Draw the hollow triangles
	if ((type == 'h') || (type == 'H'))
	{
		for (int i = 0; i < horiz_width; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				//Draws the bottom edge and top point
				if ((i == 0) || (i == horiz_width - 1))
				{
					cout << pen;
				}
				//Draws the side edges
				else if ((j == 0) || (j == i ))
				{
					cout << pen;
				}
				//Draws empty spaces in the middle
				else
					cout << " ";
			}
			cout << endl;
		}
	}
	return true;
}

//Function that asks and checks for shape height
bool input_shape_height(int& height){
	//int vertical_height;
	cout << INPUT_SHAPE_HEIGHT;
	cin >> vertical_height;
	//Make sure height is within parameters
	while (!((vertical_height >= 0) && (vertical_height <= height)))
	{
		cout << "Height must be between 0 and " << height << endl;
		//Clear the error flag on cin
		cin.clear();
		// Ignore unwanted characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> vertical_height;
	}
	return true;
}

//Function that asks and checks for shape width
bool input_shape_width(int& width){
	//int horiz_width;
	cout << INPUT_SHAPE_WIDTH;
	cin >> horiz_width;
	//Checks that width is within the inputed canvas width
	while (!((horiz_width >= 0) && (horiz_width <= width)))
	{
		cout << "Width must be between 0 and " << width << endl;
		cin.clear();
		// Ignore unwanted characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> horiz_width;
	}
	return true;
}
