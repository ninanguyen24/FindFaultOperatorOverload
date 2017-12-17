// Author: Nina Nguyen
// Filename: FindFault.cpp
// Date: 11/3/2017 (Version 2 - 10/21/2017) (Version 1 - 10/15/2017)
// Version: 3

/*Description: This class encapsulate several (FIVE) EncryptWord objects. The user has to correct input words that matches
requirements set by EncryptWord class. (4 letters, lowercase or more and no spaces or punctuations). It will encrypt or decrypt a word but adds the
notion of "corruption". The program uses a random number generator between 1-100 and then use modulo to get an odd
or even number. Even is considered false and the word won't be corrupted and Odd is considered true and will be corrupted.
Words are corrupted by appending the letter "x" to the end.  The program will assist the user in finding the
corrupted word by calling decode on the prior encrypted word. If the decrypted word dows not match the original word
sent in by the user, it will be considered corrupt.
Data structure used: arrays
Ultility function: random number generator
Dependencies: All inputs are assumed to be legal and in the correct format as required by the EncryptWord class.
Both FindFault and EncryptWord has to be in a good state.
Design: Arrays are used throughout class. Relationship between EncryptWord and FindFault will last throughout the lifetime of the class.
Error response: Program does not ultize throwing exceptions or defensive programming. Client is in charged of inputting the requested
word in the right format for program to run smoothly without crashing or returning incorrect outputs.
Modification limitations: Arrays are used and should not be changed to any other collection.
Assumptions: The client has to input the words in the right format for the class to function. (4 letters or more, all lowercase, no punctuations
and spaces). That is the only data being processed by the class. Once words are entered, it may get corrupted and the user doesn't have to interact
with the program. findQuery() will automatically be called after corruption() to assist the user in finding the corrupt word.
Decrypt is going to be used to detect corruption, if decoded strings doesn't match original string entered by user, it's corrupted.
numQuery() will be used throughout the class to keep track of corrupted words.
FindFault has-a relationship with EncryptWords, EncryptWord objects is declared in constructor and should be created once
FindFaulat is instaniated.
Operator Overload in FindFault should use Operator Overload in EncryptWord to keep the two class streamlined.
Adding two FindFault objects will manipulate them into one FindFault Object. Both words has to be corrupted in 
order for the program to add the strings together. And only the Corrupted combined string will be return. It
works just like p2. 
*/

#include "EncryptWord.h"
#include "FindFault.h"
#include <iostream> //cout and cin
#include <string>
#include <iomanip> //for setw() and setfill()
#include <ctime> //rand
#include <cstdlib> //rand

using namespace std;

FindFault::FindFault() {
	stateOfCorrupt = false;
	numOfQuery = 0;
	EncryptWord ew;
}

string* FindFault::callEncrypt(string listToEncrypt[]) {
	corruption(listToEncrypt);
	for (int i = 0; i < ARRAY_SIZE; i++) {
		string test = listToEncrypt[i];
		listToEncrypt[i] = ew[i].shift(test);
	}
	return listToEncrypt;
}

//return the state of the object - corrupt or not corrupt
bool FindFault::isCorrupt()
{
	return stateOfCorrupt;
}

//************************************************************************************************************
//**************** P3 starts below - OPERATOR OVERLOAD *******************************************************
//************************************************************************************************************

//overload operator+
//Corruption should happen to both EW Objects before it can be added together. 
//Then one long string will be returned if it's corrupted.
FindFault FindFault::operator+(const FindFault &right){
	FindFault temp;
	EncryptWord ewTemp[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; i++) {
		ewTemp[i] = (this -> ew[i] + right.ew[i]);
		listOfOriginalWords[i] = ewTemp[i].decode();
	}
	temp.callEncrypt(listOfOriginalWords);
	return temp;
}

//overload operator>
bool FindFault::operator>(const FindFault &right) {
	bool status = true;
	int count = 0;
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (ew[i] > right.ew[i]) {
			count++; //count increases if left element is larger than right element at each index
		}
	}
	if (count >= 3) { 
		status = true;
	}
	else {
		status = false;
	}
	return status;
}

//overload operator<
bool FindFault::operator<(const FindFault &right) {
	bool status = true;
	int count = 0;
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (ew[i] < right.ew[i]) {
			count++; //count increases if right element is larger than left element at each index
		}
	}
	if (count >= 3) {
		status = true;
	}
	else {
		status = false;
	}
	return status;
}

//overload operator==
bool FindFault::operator==(const FindFault &right) {
	bool status = true;
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (ew[i] == right.ew[i]) {
			status = true;
		}
		else {
			status = false;
			break; //escape loop as soon as left object does not equal right object 
		}
	}
	return status;
}

//overload operator
bool FindFault::operator!=(const FindFault &right) {
	bool status = true;
	for (int i = 0; i < ARRAY_SIZE; i++) {
		if (ew[i] != right.ew[i]) {
			status = true;
		}
		else {
			status = false;
			break; //escape loop as soon as left object equal right object 
		}
	}
	return status;
}

//corrupt the words
string* FindFault::corruption(string listFromUser[]) {
	for (int i = 0; i < ARRAY_SIZE; i++) {
		listOfOriginalWords[i] = listFromUser[i];//copy the original words from client class to another array
	}

	srand((unsigned)time(NULL));//has to be outside loop for random number to be different each time
	for (int i = 0; i < ARRAY_SIZE; i++) {
		string addToWord = "x";
		int randomNum = ((rand() % 100) + 1) % 2; //gets odd or even
		if (randomNum == 0) {//false - won't corrupt
			continue;
		}
		else {//true - corrupt
			listFromUser[i].append(addToWord);
			stateOfCorrupt = true;
			numOfQuery++;
		}
	}
	return listFromUser;
}

void FindFault::faultQuery() {//use decoding to find the faulty word, needs to be in corrupt state
	const int NUM_WIDTH = 30;
	const char SEPARATOR = ' ';
	if (stateOfCorrupt) {
		string decryptWord = "";
		int size = 0;
		cout << "The following words are corrupted and has the letter \"x\" added to the end of the it." << endl;
		cout << "***************************************************************************" << endl;
		cout << left << setw(NUM_WIDTH) << setfill(SEPARATOR) << "Original Word";
		cout << left << setw(NUM_WIDTH) << setfill(SEPARATOR) << "Corrupted Decrypt Word";
		cout << left << setw(NUM_WIDTH) << setfill(SEPARATOR) << "Corrupted Index" << endl;
		cout << "***************************************************************************" << endl;
		for (unsigned int i = 0; i < ARRAY_SIZE; i++) {
			decryptWord = ew[i].decode();
			if (decryptWord != listOfOriginalWords[i]) {
				size = decryptWord.size();
				cout << left << setw(NUM_WIDTH) << setfill(SEPARATOR) << listOfOriginalWords[i];
				cout << left << setw(NUM_WIDTH) << setfill(SEPARATOR) << decryptWord;
				cout << left << setw(NUM_WIDTH) << setfill(SEPARATOR) << size << endl;
			}
		}
		cout << endl;
		cout << "Total number of faulty encrypted words are: " << numOfQuery << endl;
	}
	else {
		cout << "There are no corrupted words." << endl;
	}
}

int FindFault::statistics() {
	return numOfQuery;
}
