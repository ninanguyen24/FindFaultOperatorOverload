// Author: Nina Nguyen
// Filename: p3.cpp
// Date: 11/2/2017
// Version: 1


/*
This program will demostate the use of Operator Overload to add and compare to objects. Test arrays of size 5 were
created to test the operators. Users won't be asked to enter any input so there should be no
errors handling. FindFault holds 5 EncryptWord object in it's collection so when you compare the two FindFault objects,
each index of the FindFault objects would be compared to each other.
For example, FindFault_1[0] will be compared to FindFault_2[0] and so on. Assuming that FindFault_1[0] will not be compared
out of index like FindFault_2[2];

Data Structure used: Array is used to hold 5 strings to pass into FindFault
Class used with functionality: FindFault (callEncrypt(Array) and Operator Overload)
Ultility Functions used: iomanip to format cout, string and iostream for cout.
Value ranges: Array size is set to 5
Format of output: cout
No input will be used.
Design and intent: Driver is used to demostate the use of operator overloading for FindFault. It will print out various results
				   from tests.
Errors: No inputs are accepted. Assuming that the client can compare their own FindFault objects, the words has to be
	    four letters or more and cannot compare FindFault objects to other objects. FindFault objects has to be in a
		valid state.

Operator overload were added, state has to be on when they're called. The client can call the operator overload
to compare two find fault objects in the main. FindFault operator overload has to use EncryptWord overload to keep
the two class streamlined.

Operator> and Operator< will compare the two collection in FindFault and the object with the higher count of passed test
conditions will be the one with higher or lesser. For example, FindFault1 is holding strings with 4,5,5,6,7 and FindFault2
is holding strings with 4,5,6,7,8 means FindFault2 have 3 indexes higher than FindFault1.

Operator== and Operator!= if one index fails, the rest of the test fails.

Operator+ will combine the two words in EncryptWord objects at each indexes to make one long word. The words will only be added
if it's in a corrupt state and the new string will have callEncrypt() and faultQuery() will be called on the new string and will
be returned if it's corrupted.

Assumption: EncryptWOrd is encapsulated and is being tested through FindFault since FindFault calls on the EncryptWord operator
overload for it's own overloading.

Can only use operator overloading if the objects were instantiated properly.
*/
#include "FindFault.h"
#include "EncryptWord.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


//Short introduction for P3 
void introForP3() {
	cout << "This program demostrates how you can use Operator Overloading to \n";
	cout << "add or compare two user defined objects. The program will use the length \n";
	cout << "of the word as a basis for comparison. Each FindFault object takes in an array \n";
	cout << "of 5 strings in it's collection. You can compare the two Findfault objects or add the \n";
	cout << "objects together to make one FindFault object." << endl;
	cout << endl;
	cout << "When using \"<\" or \">\" operators, the FindFault object with 3 or more words that \n";
	cout << "are longer will pass the condition." << endl;
	cout << endl;
	cout << "For \"==\" and \"!=\" operators, if one index fails the test, obviously the whole object fails." << endl;
	cout << endl;
	cout << "When adding two FindFault objects together, the program will combine the two words at \n";
	cout << "each respective indexes to make another FindFault object with one long word. For example, \n";
	cout << "\"hello\" and \"world\" will be appended if they are in the correct state." << endl;
	cout << endl;
	cout << "Let's begin!" << endl;;
	cout << "*****************************************************************************************" << endl;
	cout << endl;
}

//Prints out the values in the array that's passed into the method
void printArray(string arr[], int numOfArray) {
	for (int j = 0; j < ARRAY_SIZE; j++) {
		cout << "Test Array" << numOfArray << " " << j + 1 << ": " << setw(10) << arr[j];
		cout << setw(20) << "Length of word: " << arr[j].length() << endl;
	}
	cout << endl;
}


//Description: Four test arrays of five strings were created to test the Operator Overloads. The driver will
//print out the test arrays and demostate the comparing and adding of FindFault objects
//Program does not accept any inputs from users
int main() {

	introForP3();

	string testArray1[] = { "hello", "world", "rained", "book","alph" }; //String length: 5,5,6,4,4
	string testArray2[] = { "phone", "chaired", "snows", "water", "bowls" };//String length: 5,7,5,5,5
	string testArray3[] = { "five", "four", "thee", "twod", "bone" }; //String length: 4,4,4,4,4
	string testArray4[] = { "moon", "star", "ezio", "dote", "lone" }; // String length: 4,4,4,4,4
	FindFault ff, ff2, ff3, ff4, ff5;

	//print out test arrays
	cout << "The following arrays of words are going to be used to demostrate Operator Overload." << endl;
	printArray(testArray1, 1);
	printArray(testArray2, 2);
	printArray(testArray3, 3);
	printArray(testArray4, 4);

	//instantiate FindFault objects
	ff.callEncrypt(testArray1);
	ff2.callEncrypt(testArray2);
	ff3.callEncrypt(testArray3);
	ff4.callEncrypt(testArray4);

	cout << "Test Array 1 > Test Array 2: " << boolalpha << (ff > ff2) << endl;
	cout << "Test Array 1 < Test Array 3: " << boolalpha << (ff < ff3) << endl;
	cout << "Test Array 2 < Test Array 1: " << boolalpha << (ff2 < ff) << endl;
	cout << "Test Array 2 > Test Array 1: " << boolalpha << (ff2 > ff) << endl;
	cout << "Test Array 3 equals Test Array 4: " << boolalpha << (ff3 == ff4) << endl;
	cout << "Test Array 1 equals Test Array 4: " << boolalpha << (ff == ff4) << endl;
	cout << "Test Array 2 does not equal Test Array 3: " << boolalpha << (ff2 != ff3) << endl;

	cout << endl;
	cout << "Test Array 1 + Test Array 2: FindFault will return the combined word if itself is corrupted.";
	cout << endl;
	ff5 = ff + ff2; //add two FindFault objects together and put into a new one.
	cout << endl;
	ff5.faultQuery(); //help the user find what word is corrupted after adding of two objects

}

