//
// CS31 Winter 2015
// File: HW #3-Vintage Graphics_vintage
// Author: Katherine Sheu (katherinesheu@ucla.edu)
// SID: 304150980
// Date: 2015-1-30
// Version: 1.0
// Description: Software for vintage graphics using ASCII characters
//				User inputs: canvas_size, pen, shape, shape type, height, width
//				Output: geometric shapes using ASCII chracters

#include<iostream>
#include<string>
#include<cctype>
#include<limits>
#include<cmath>
#include"vgraphlib.h"
using namespace std;



int main(){

	int menu_choice;
	int shape_choice;
	bool not_exit = true;
	bool canvas_entered = false;
	bool pen_entered = false;
	

	const string MAIN_MENU_HEADER = "====================================\nvintage v1.0 - Copyright 2015 Simba\n";
	const string MAIN_MENU_CHOICES = "Make the following selection:\n1 - Set up the canvas\n2 - Select the pen\n3 - Draw the shape\n4 - Exit\n";
	const string MAIN_MENU_CLOSING = "====================================\n";
	const string SHAPE_MENU_CHOICES = "Select the shape you'd like to draw:\n1 - Vertical line\n2 - Horizontal line\n3 - Rectangle\n4 - Right triangle\n5 - Return to Main Menu\n";
	const string INCORRECT_OPTION = "Incorrect options. Try again";
	
	
	//sets up the main menu loop
	while (not_exit)
	{
		bool not_main = true;
		cout << MAIN_MENU_HEADER;
		cout << MAIN_MENU_CHOICES;
		cout << MAIN_MENU_CLOSING;

		//accepts user input for a menu choice
		cin >> menu_choice; 
		//only accepts menu choices that are valid options
		while (!((menu_choice == 1) || (menu_choice == 2) || (menu_choice == 3) || (menu_choice == 4)))
		{
			cout << INCORRECT_OPTION << endl;
			
			// Clear error flags
			cin.clear();

			// Ignore unwanted characters
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cin >> menu_choice;
		}
		//ignore anything leftover, if double in range 1-4 take the first thing in stream (truncate the decimal)
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (menu_choice)
		{
		case 1:
			int pic_h, pic_w;
			//Checks to make sure canvas is set up properly
			if (cmd_canvas_setup(pic_h, pic_w) == true){
				canvas_entered = true;
				//cout << "Function call successful." << endl;
			}
			
			break;
		
		case 2:
			char ascii_char;
			//checks to make sure pen is set up properly
			if (cmd_pen_selection(ascii_char)==true){
				pen_entered = true;
				//cout << "case 2 call successful" << endl;
			}
			
			break;

		case 3:
			//makes sure that 1&2 are set up correctly before 3
			//display separate error messages depending on what is set up so far
			if (canvas_entered == false && pen_entered == false){
				cout << "Canvas must be set up first.\n";
				cout << "Pen must be selected first.\n";
				break;
			}
			if (canvas_entered == false){
				cout << "Canvas must be set up first.\n";
				break;
			}
			if (pen_entered == false){
				cout << "Pen must be selected first.\n";
				break;
			}
			
			//sets up shape menu loop
			while (not_main)
			{

				cout << MAIN_MENU_HEADER;
				cout << SHAPE_MENU_CHOICES;
				cout << MAIN_MENU_CLOSING;
				//ask for user input for shape menu
				cin >> shape_choice;
				//make sure shape menu input is valid
				while (!((shape_choice == 1) || (shape_choice == 2) || (shape_choice == 3) || (shape_choice == 4) || (shape_choice == 5)))
				{
					cout << INCORRECT_OPTION <<endl;
					// Clear error flags
					cin.clear();

					// Ignore unwanted characters
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> shape_choice;
				}
				//ignore anything left over, if double, then truncate
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				switch (shape_choice)
				{
				//if 1, draw vertical line
				case 1:
					
					cmd_draw_vertical_line(ascii_char, pic_h);
					break;
				//if 2, draw horizontal line
				case 2:
					
					cmd_draw_horizontal_line(ascii_char, pic_w);
					break;
				//if 3, draw rect.
				case 3:
					//asks for the type of shape to be drawn
					char pic_type;
					cout << "Input the type: ";
					cin >> pic_type;
					//reject incorrect input
					while (!((pic_type == 'h') || (pic_type == 'H') || (pic_type == 's') || (pic_type == 'S')))
					{
						cout << "Type must be H/h or S/s" << endl;
					
						cin >> pic_type;
					}
					
					if(cmd_draw_rectangle(ascii_char, pic_type, pic_h, pic_w)==true)
						break;

				//if 4, draw right triangle
				case 4:
					
					cout << "Input the type: ";
					cin >> pic_type;
					while (!((pic_type == 'h') || (pic_type == 'H') || (pic_type == 's') || (pic_type == 'S')))
					{
						cout << "Type must be H/h or S/s" << endl;
						
						cin >> pic_type;
					}
					// pass in the value of the lowest of height and width
					if(cmd_draw_right_triangle(ascii_char, pic_type, fmin(pic_w, pic_h))==true)
						break;
				//if 5, not_main = false, break, continue.
				case 5:
					// exit the shape menu
					not_main = false;
					break;
				default:
					cout << "shape menu, uh oh\n";
				}
			}
			break;
		case 4:
			cout << "Thank you. Bye now.\n";
			not_exit = false;
			break;
		default:
			cout << "UH OH!";
		}
	}
	return 0;
}
