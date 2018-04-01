//
// CS31 Winter 2015
// File: HW #4 – Here's to the Songs!
// Author: Katherine Sheu (katherinesheu@ucla.edu)
// SID: 304150980
// Date: 2015-2-23
// Version: 1.0
// Description: Skootify software for song documentation
//

#include<string>
//#define NDEBUG
#include<cassert>
#include<iostream>
using namespace std;

enum SPI_Class
{
	SPI_PLATIUM = 1,
	SPI_GOLD,
	SPI_SILVER,
	SPI_COPPER,
	SPI_PAPER 
};
enum SPI_Change {
	SPI_CHANGE_NO = 0,
	SPI_CHANGE_UP = 1,
	SPI_CHANGE_DOWN = -1
};

//function prototypes
int computeSPI(SPI_Class spi[], SPI_Change spi_change[], const int
	votes[], const bool grammy[], int size);

int getRankingList(const SPI_Class spi[], SPI_Class spi_class, int
	songList[], int size);

int getChangeList(const SPI_Change spi_change[], SPI_Change 
	an_spi_change, int songList[], int size);

int getGrammyList(const bool grammy[], int songList[], int size);

int merge(const string a1[], int size1, const string a2[], int size2,
	string result[], int size);

int deleteDuplicates(string a[], int size);

int moveToStart(string a[], int n, int loc);

int moveToEnd(string a[], int n, int loc);
//global constants
const int TOTAL_NO_SONGS = 1000;

int main(){
	
	string song[TOTAL_NO_SONGS];
	string singer[TOTAL_NO_SONGS];
	SPI_Class spi[TOTAL_NO_SONGS];
	int votes[TOTAL_NO_SONGS];
	bool grammy[TOTAL_NO_SONGS];

	//testing function 1
	SPI_Class some_spis[4] = { SPI_SILVER, SPI_COPPER, SPI_GOLD,
		SPI_COPPER };
	int some_votes[4] = { 5400, 400, 6000, 600 };
	bool some_grammy[4] = { false, false, false, true };
	SPI_Change some_changes[4];
	int i = computeSPI(some_spis, some_changes, some_votes, some_grammy,
		4);
	cout << "Testing for function 1 " << i << endl;
	for (int i = 0; i < 4; i++){
		cout << some_spis[i] << endl;
	}
	for (int i = 0; i < 4; i++){
		cout << some_changes[i] << endl;
	}
	// Now some_spis is SPI_GOLD, SPI_PAPER, SPI_GOLD,
	// SPI_PLATINUM
	// and some_changes is SPI_CHANGE_UP, SPI_CHANGE_DOWN,
	// SPOI_CHANGE_NO, SPI_CHANGE_UP

	//test function 2
	int song_list[4];
	int k = getRankingList(some_spis, SPI_PLATIUM, song_list, -1);
	cout << "Testing function 2 " << k<< endl;
	for (int i = 0; i < 4; i++){
		cout << song_list[i] << endl;
	}


	//test function 6
	string favorite[8] = {"Style", "If", "Clean", "Clean", "Heaven", "Heaven", "If", "If"};
	int n = deleteDuplicates(favorite, 8);
	cout << "Testing for delete dup " << n<< endl;
	for (int i = 0; i < 8; i++){
		cout << favorite[i] << endl;
	}

	//test function 5
	string jazz[4] = { "Take Five", "So What ? ", "Angela", "Affirmation"};
	string rap[3] = { "YG my hitter", "Drake trophies", "B.o.b headband" };
	string z[30];
	int m = merge(jazz, 4, rap, 3, z, 30);
	cout << "Testing merge function " << m << endl;
	for (int i = 0; i < m; i++){
		cout << z[i] << endl;
	}

	//test function 7
	string favorites[6] = {"Style", "If", "So What ?", "Clean", "Heaven", "Take Five"};
	int r = moveToStart(favorites, 6, 3); // returns 3
	cout << "Test for move to start " << r<< endl;
	for (int i = 0; i < 6; i++){
		cout << favorites[i] << endl;
	}

	//test function 8
	int r2 = moveToEnd(favorites, 6, 3); // returns 3
	cout << "Test for move to end " << r2 << endl;
	for (int i = 0; i < 6; i++){
		cout << favorites[i] << endl;
	}
	
}

/*	precondition: array size is >= 0
	postcondition:*/
int computeSPI(SPI_Class spi[], SPI_Change spi_change[], const int votes[], const bool grammy[], int size){
	//return -1 if bad input
	//assert(size >= 0 && size <= TOTAL_NO_SONGS);
	if (size < 0 || size > TOTAL_NO_SONGS){
		return -1;
	}
	//assign class based on votes
	for (int i = 0; i < size; i++){
		SPI_Class temp = spi[i];
		if (votes[i] >= 5000){
			spi[i] = SPI_GOLD;
		}
		else if (votes[i] >= 2000){
			spi[i] = SPI_SILVER;
		}
		else if (votes[i] >= 500){
			spi[i] = SPI_COPPER;
		}
		else{
			spi[i] = SPI_PAPER;
		}
		//grammy trumps all 
		if (grammy[i] == true){
			spi[i] = SPI_PLATIUM;
		}

		//record the change from previously
		if (spi[i] == temp){
			spi_change[i] = SPI_CHANGE_NO;
		}
		else if (spi[i] >= temp){
			spi_change[i] = SPI_CHANGE_DOWN;
		}
		else
			spi_change[i] = SPI_CHANGE_UP;
	}
	return 0;
}

int getRankingList(const SPI_Class spi[], SPI_Class spi_class, int songList[], int size){
	//assert(size >= 0 && size <= TOTAL_NO_SONGS);
	if (size < 0 || size > TOTAL_NO_SONGS){
		return -1;
	}
	//add to the songList array if it matches the key
	songList[size];
	int count = 0;
	for (int i = 0; i < size; i++){
		if (spi[i] == spi_class){
			songList[count] = i;
			count++;
		}
	}
	//add -1 to say end of useful data
	songList[count] = -1;
	return 0;
}

//this function uses the same algorithm as getRankingList
int getChangeList(const SPI_Change spi_change[], SPI_Change an_spi_change, int songList[], int size){
	//assert(size >= 0 && size <= TOTAL_NO_SONGS);
	if (size < 0 || size > TOTAL_NO_SONGS){
		return -1;
	}
	songList[size];
	int count = 0;
	for (int i = 0; i < size; i++){
		if (spi_change[i] == an_spi_change){
			songList[count] = i;
			count++;
		}
	}
	songList[count] = -1;
	return 0;
}

//This function uses same algorithm as getRankingList
int getGrammyList(const bool grammy[], int songList[], int size){
	//assert(size >= 0 && size <=TOTAL_NO_SONGS);
	if (size < 0 || size > TOTAL_NO_SONGS){
		return -1;
	}
	songList[size];
	int count = 0;
	//adds to array if true
	for (int i = 0; i < size; i++) {
		if (grammy[i] == true){
			songList[count] = i;
			count++;
		}
	}
	songList[count] = -1;
	return 0;
}

/*postcondition: size1+size2 <=size*/
int merge(const string a1[], int size1, const string a2[], int size2, string result[], int size){
	//assert(size >= 0 && (size1 + size2) <= size);
	if (((size1 + size2) > size) || (size<0)){
		return-1;
	}
	//return -1 if neither array is non increasing
	for (int i = 0; i < size1-1; i++){
		if ((a1[i] < a1[i + 1])){
			return -1;
		}
	}
	for (int i = 0; i < size2 - 1; i++){
		if ((a2[i] < a2[i + 1])){
			return -1;
		}
	}
	
	//Place the first array into result
	for (int i = 0; i < size1; i++){
		result[i] = a1[i];
	}
	//place the second array into result after elements of first array
	for (int i = 0; i < size2; i++){
		result[i+size1] = a2[i];
	}

	//do a selection sort by finding largest element and placing that in front
	for (int i = 1; i < size1 + size2; i++){
		string max = result[i];
		int j = i;
		while (j > 0 && result[j - 1] < max){
			result[j] = result[j - 1];
			j--;
		}
		result[j] = max;
	}
	return (size1 + size2);
	
}

int deleteDuplicates(string a[], int size){
	int current_size = size;
	for (int i = 1; i < size; i++){
		//works for three in a row
		if (a[i] == a[i - 1]){
			moveToEnd(a, size, i);
			current_size--;
		}
	}
	return current_size;
}

int moveToStart(string a[], int n, int loc){
	//assert(loc < n);
	if (loc >= n){
		return -1;
	}
	//store, shift everything else, then put it at the beginning
	string temp = a[loc];
	for (int i = loc; i > 0; i--){
		a[i] = a[i - 1];
	}
	a[0] = temp;
	return loc;
}

int moveToEnd(string a[], int n, int loc){
	//assert(loc < n);
	if (loc >= n){
		return -1;
	}
	//store, shift everything else, then put it at the end
	string temp = a[loc];
	for (int i = loc; i < n - 1; i++){
		a[i] = a[i + 1];
	}
	a[n - 1] = temp;
	return loc;
}
