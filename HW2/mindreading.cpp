//
// CS31 Winter 2015
// File: HW #2 – Reading My Mind
// Author: Katherine Sheu (katherinesheu@ucla.edu)
// SID: 304150980
// Date: 2015-1-20
// Version: 1.0
// Description: Random number guessing game for children
//

#include<string>;
#include<cstdlib>;
#include<ctime>;
#include<cmath>;
#include<iostream>
using namespace std;


int main(){
	//These variables are declared here and will be initialized with user input.
	string name;
	int level;
	int smallInt;
	int largeInt;
	string playAgain;

	//counts the number of games won
	int winCount = 0;
	
	/*This variable is initialize to -1 since the target random number will always be positive.
	It will be reassigned when the user inputs a guess.*/
	int guess = -1;
	//The random number generator is seeded with the current time to better reporduce randomness.
	srand(static_cast<int>(time(0)));
	int numGuesses;
	int guessCount;

	//output the heading for the game
	cout << "== == == == == == == == == == == == == == == == == == ==" << endl;
	cout << "Mindreading(v1.0)" << endl;
	cout << "Copyright 2015 Bruinie\n" << endl;
	cout << "Welcome to Mindreading Game!" << endl;
	cout << "Good luck and have fun!" << endl;
	cout << "== == == == == == == == == == == == == == == == == == ==" << endl;
	cout << "Please make the following selections :" << endl;

	cout << "Your name: ";
	getline(cin, name);
	//Keep prompting if no name is entered.
	while (name == ""){
		cout << "You must enter your name." << endl;
		getline(cin, name);
	}


	cout << "Level of Difficulty (1 - Easy; 2 - Hard): ";
	cin >> level;
	//Keep prompting if level entered is not 1 or 2.
	while (!((level == 1) || (level == 2))){
		cout << "Level of difficulty must be 1 (Easy) or 2 (Hard)." << endl;
		cin >> level;
	}
	//Ask for smallest integer and keep prompting if integer is not positive.
	cout << "The smallest positive integer you want to guess: ";
	cin >> smallInt;
	while (smallInt <= 0){
		cout << "It must be a positive integer." << endl;
		cin >> smallInt;
	}
	////Ask for largest integer and keep prompting if integer is not positive.
	cout << "The largest positive integer you want to guess: ";
	cin >> largeInt;
	while (largeInt <= 0){
		cout << "It must be a positive integer." << endl;
		cin >> largeInt;
	}
	//After making sure it is positive, then check to make sure largest is greater than smallest.
	while (largeInt <= smallInt){
		cout << "The biggest integer must be greater than the smallest integer." << endl;
		cin >> largeInt;
	}

	//This block will be executed once in the beginning, and again every time the user inputs "Y" for a new game. 
	do {
		//Generate a new random number for every iteration of the game.
		int range = largeInt - smallInt + 1;
		int targetRandInt = rand() % range + smallInt;

		//Ask user to input a number in the specified range for every repeat of the game.
		cout << "Awesome, " << name << "! I'm thinking of an integer between " << smallInt << " and " << largeInt << ". Make a guess."<<endl;

		/*Reset guess for continuous iterations of the game just in case the generated random number is the same as before. Otherwise, the targetRandInt
		will match the guess immediately, even though the guess was from the previous round. 
		*/
		guess = -1;
		//Reset the guessCount to 0 for every iteration of the game.
		guessCount = 0;

		//Depending on the level stored during the initial input phase, different outputs or hints are provided. 
		switch (level)
		{
		case 1:
			//Calculates the number of guesses allowed. 
			numGuesses = ceil(0.8*log2(range));
			//remove this later
			//cout << "You have " << numGuesses << " guesses.\n";


			//Keep asking for guesses while the number is not correct and the user still has guesses left.
			while ((guess != targetRandInt) && (guessCount < numGuesses))
			{
				cin >> guess;
				guessCount++;
				//Aborts all following game play if -1 is entered as a guess.
				if ((guess == -1))
				{
					cout << "Sorry, " << name << "! Goodbye!" << endl; 
					return 0;
				}
				//Prevents the printing of the hint and exit prompt if this is the last guess.
				if (guessCount == numGuesses)
				{
					break;
				}
				//Printing the hint messages only for case 1. 
				else if (guess < targetRandInt)
				{
					cout << "Sorry, " << name << "! I'm thinking of a larger number. Try again or enter -1 to exit." << endl;
				}
				else if (guess > targetRandInt)
				{
					cout << "Sorry, " << name << "! I'm thinking of a smaller number. Try again or enter -1 to exit." << endl;
				}
				

			}
			//If the guess is correct at any point or on the last try, print the statistics.
			if (guess == targetRandInt)
			{
				cout << "Congratulations, " << name << "! You guessed the secret number " << targetRandInt << "!" << endl;
				cout << "<Play Statistics>\n- Name: " << name << "\n- Level : " << level << "\n- Total number of times to guess " << targetRandInt << ": " << guessCount << endl;
				//increments number of games won to determine which goodbye message should be outputed later.
				winCount++;
			}
			//Else the number of guesses has been exceeded without getting the correct number, so print the game over message.
			else
			{
				cout << "Sorry, " << name << "! Game Over!" << endl;
			}
			break;
		
		//Case 2 works the same way except the number of guesses allowed is lower, and no hints are printed.
		case 2:
			//Calculate the number of guesses allowed.
			numGuesses = ceil(0.4*log2(range));
			//remove this later
			//cout << "You have " << numGuesses << " guesses.\n";

			while ((guess != targetRandInt) && (guessCount < numGuesses))
			{
				cin >> guess;
				guessCount++;
				if ((guess == -1))
				{
					cout << "Sorry, " << name << "! Goodbye!" << endl;
					return 0;
				}
				//Prevents the printing of the hint and exit prompt if this is the last guess.
				if (guessCount == numGuesses)
				{
					break;
				}
				else if (guess < targetRandInt)
				{
					cout << "Sorry, " << name << "! Try again or enter -1 to exit." << endl;
				}
				else if (guess > targetRandInt)
				{
					cout << "Sorry, " << name << "! Try again or enter -1 to exit." << endl;
				}

				
			}
			if (guess == targetRandInt)
			{
				cout << "Congratulations, " << name << "! You guessed the secret number " << targetRandInt << "!" << endl;
				cout << "<Play Statistics>\n- Name: " << name << "\n- Level : " << level << "\n- Total number of times to guess " << targetRandInt << ": " << guessCount << endl;
				winCount++;
			}
			else
			{
				cout << "Sorry, " << name << "! Game Over!" << endl;
			}
			break;

		/*Ideally, this block should neve be reached since the earlier code block prevents the user 
		from entering any level other than 1 or 2.*/
		default:
			cout << "ERROR!";
		}

		//Ask if user wants a new game, keep prompting if incorrect input provided.
		cout << "Do you want to play another game (Y/N)?" << endl;
		cin >> playAgain;
		while (!((playAgain == "Y") || (playAgain == "N"))){
			cout << "You must enter either Y or N." << endl;
			cin >> playAgain;
		}

	
	} while (playAgain == "Y");

	//If "N" is entered, print the thank you statement only if the user has won at least once. 
	if (winCount == 0)
	{
		cout << "Sorry, " << name << "! Goodbye!" << endl;
	}
	else
	{
		cout << "Thank you for reading my mind, " << name << "! Goodbye!" << endl;

	}
	
	return 0;

}