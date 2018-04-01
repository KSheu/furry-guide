// Dictionary.cpp
// Takes user input of any string 
// Displays anagrams that are actual words in the words file. 
// Date: 2015-06-03
// Version: 1.0

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <algorithm>  // for swap
#include <iostream> //for testing
using namespace std;

void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// This class does the real work of the implementation.


class DictionaryImpl
{
public:
	DictionaryImpl() {}
	~DictionaryImpl() {}
	void insert(string word);
	void lookup(string letters, void callback(string)) const;
private:
	//list<string> m_words;
	list<string> hasharray[50000];
};

/*Hash function for strings*/
int hashword(const string str)
{
	unsigned long hash = 5381;

	for (string::const_iterator p = str.begin(); p != str.end(); p++)
		hash = ((hash << 5) + hash) + *p; // hash * 33 + character 

	return (static_cast<int>(hash % 50000));
}

/*Sorts the letters in a word alphabetically*/
string sortword(string word){
	string sorted = word;
	for (int i = 0; i<sorted.length() - 1; i++)
	{
		for (int j = i + 1; j<sorted.length(); j++)
		{
			if (sorted[i] > sorted[j])
			{
				char temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
		}
	}
	return sorted;
}

void DictionaryImpl::insert(string word)
{
	removeNonLetters(word);
	string entrytoAdd = word;

	if (!word.empty()){ //if valid word

		int item_hash_index = hashword(sortword(word)); //sort word for the key and find a place to hash it
	
		hasharray[item_hash_index].push_back(entrytoAdd); //anagrams hash to the same location
		
	}
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
	if (callback == nullptr)
		return;

	removeNonLetters(letters);
	if (letters.empty())
		return;

	
	int bucket = hashword(sortword(letters)); // get the key for the group of letters to determine where to look

	list<string> curr = hasharray[bucket]; //for convenience

	//iterate through the list
	for (list<string>::iterator wordp = curr.begin(); wordp != curr.end(); wordp++){ 
	
		if (sortword(letters) == sortword(*wordp)){ //if same letters then is anagram
			callback(*wordp);
		}
	}
}

void removeNonLetters(string& s)
{
	string::iterator to = s.begin();
	for (string::const_iterator from = s.begin(); from != s.end(); from++)
	{
		if (isalpha(*from))
		{
			*to = tolower(*from);
			to++;
		}
	}
	s.erase(to, s.end());  // chop off everything from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"

void generateNextPermutation(string& permutation)
{
	string::iterator last = permutation.end() - 1;
	string::iterator p;

	for (p = last; p != permutation.begin() && *p <= *(p - 1); p--)
		;
	if (p != permutation.begin())
	{
		string::iterator q;
		for (q = p + 1; q <= last && *q > *(p - 1); q++)
			;
		swap(*(p - 1), *(q - 1));
	}
	for (; p < last; p++, last--)
		swap(*p, *last);
}

//******************** Dictionary functions **********************************

// These functions simply delegate to DictionaryImpl's functions.

Dictionary::Dictionary()
{
	m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
	delete m_impl;
}

void Dictionary::insert(string word)
{
	m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
	m_impl->lookup(letters, callback);
}
