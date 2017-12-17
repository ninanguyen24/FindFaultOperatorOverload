// Author: Nina Nguyen
// Filename: FindFault.h
// Date: 11/3/2017 (Version 2 - 10/21/2017) (Version 1 - 10/15/2017)
// Version: 3


/*Description: This class encapsulate several (FIVE) EncryptWord objects. The user has to correct input words that matches
requirements set by EncryptWord class. (4 letters, lowercase or more and no spaces or punctuations). It will encrypt or decrypt a word but adds the
notion of "corruption". The program uses a random number generator between 1-100 and then use modulo to get an odd
or even number. Even is considered false and the word won't be corrupted and Odd is considered true and will be corrupted.
Words are corrupted by appending the letter "x" to the end of the string.  The program will assist the user in finding the
corrupted word by calling decode on the prior encrypted word. If the decrypted word dows not match the original word
sent in by the user, it will be considered corrupt.

Class used: EncryptWord
Legal States: With dependencies on EncryptWord state of "on" or "of", FindFault class will either be "corrupt" or "not corrupt"
Legal and illegal inputs: The program requires for the user to input the words to be encrypted as documented in EncryptWord.
There is no guarantee the class will work if the input is not entered as required. There are no exceptions
or defensive programming in placed to catch illegal inputs.
Ownership: Will not pass EncryptWord objects or share EncryptWord with other objects
State transitions: not corrupt to corrupt occurs when the array with legal words are passed into callEncrypt()
is called. Once corruption is called the state will remain unchanged until the program exits.
Functionality: callEncrypt() function takes in an array of strings and call the corruption() function to see if the word should be corrupted.
It will return a different array after corruption. That state changes to "corrupt" after function is
called if one of the words were corrupted.
Then callEncrypt() call the shift() method in encryptWord to encrypt the word. encryptWord class does
not know if words have been tempered with or not.
isCorrupt() will return the current state of the object (corrupt or not corrupt). It is initially set to "false" when the constructor is called,
if a word was corrupted, it will be set to "true"
Cardinality: FindFault can have one to many EncryptWord objects but EncryptWord objects can have one and only one FindFault.
Interface Invariants: Can't assign one object to another object. All words in arrays meet requirements. Corrupt state is true throughout
once the word has been affected.
Class Invariants: The class will only work if ARRAY_SIZE remained unchanged. Both driver and class are dependent on the variable.
FindFault class will always have encryptWord objects even if it's null.
listOfOriginalWords array will hold the orginal words passed in by the user, will not be changed throughout the class.
numOFQuery() cannot be less than 0.
isCorrupt() is used to test the current state of the FindFault class.
faultQuery() won't be called before callEncrypt(). If none of the words were corrupted - faultQuery() won't be called
Assumptions: Lifetime association between EncryptWord and FindFault. faultQuery() will return original word, corrupted word and index.
Class is assumed to work only if the user input correct words. Encrypted word might be corrupted, there's no definite that
it's always corrupted. FindQuery() can only be called when the state of the object is corrupt.
Hence, it's dependent on isCorrupt() to return the current state.

Operator overloading uses a bottom-up method. EncryptWord class will hold the main functionality of Operator overload and
FindFault class will use that as a basis of it's operator overloading. 

Operator overload were added, state has to be on when they're called. The client can call the operator overload 
to compare two find fault objects in the main. FindFault operator overload has to use EncryptWord overload to keep 
the two class streamlined. 

Operator> and Operator< will compare the two collection in FindFault and the object with the higher count of passed test 
conditions will be the one with higher or lesser. For example, FindFault1 is holding strings with 4,5,5,6,7 and FindFault2
is holding strings with 4,5,6,7,8 means FindFault2 have 3 indexes higher than FindFault1.

Operator== and Operator!= if one index fails, the rest of the test fails.

Operator+ will combine the two words in EncryptWord objects at each indexes to make one long word. The words will only be added
if it's in a valid instantiated state and the new string will have callEncrypt() and faultQuery() will be called on the new string and will
be returned if it's corrupted. faultQuery() will be used in main to test the addition of two FindFault objects. 

Assumption: Cannot compare or add EncryptWord with FindFault objects.
*/

#ifndef FINDFAULT_H
#define FINDFAULT_H
#pragma once

#include "EncryptWord.h"
#include<iostream>
using namespace std;

static const int ARRAY_SIZE = 5; //set the number of words that will be accepted by the class. Words will be added to array,.

class FindFault : public EncryptWord {

public:
	//description: FindFault constructor. Calls the EncryptWord class constructor and create an array
	//pre: none
	//post: none
	FindFault();

	//Helps find fault through decoding, will print out the decrypted corrupted words calls the statistics method
	//pre: can only be called with state is "corrupt" -- one or more words in the array must be corrupted to be in corrupt state.
	//post: none
	void faultQuery();

	//description: This method is called after words are entered by the user. It will call corruption() function to corrupt
	//the words before calling EncryptWord methods to encrypt the word. Returns the updated encrypted word array.
	//Some words may be corrupted.
	//pre: the state of the object is in a "not corrupt" state at the beginning of the function call
	//post: the state transition to may be "corrupt" or may not be corrupt
	string* callEncrypt(string[]);

	//description: returns the current state of the object to make sure that findQuery() can be called. Method is dependentant
	//on the stateOfCorrupt boolean. stateOfCorrupt boolean will be set to true when words are corrupted.
	//pre: none
	//post: none
	bool isCorrupt();

	//************************************************************************************************************
	//**************** P3 starts below - OPERATOR OVERLOAD *******************************************************
	//************************************************************************************************************

	//description: Add the EncryptWord objects within the FindFault objects together using the overload operators in 
	//			   EncryptWord. (Eg. FindFault[0] will be added to FindFault2[0]). Array will have hold the new combined
	//			   words. Return a FF object with corrupted - callEncrypt() will be called with the new array of 
	//			   strings to instantiate and give functionality to the new FF object.
	//pre: Both FindFault objects may or may not be corrupted
	//post: Return a single corrupted string 
	FindFault operator+(const FindFault &);

	//description: Greater than comparison - Compare the string length of of each FindFault indexes holding an
	//			   EncryptWord object. Default array size is 5, so whichever object has 3 or more longer strings 
	//			   will be the greater object. Return true or false.
	//pre: Both FindFault objects may or may not be corrupted
	//post: No change to state
	bool operator > (const FindFault &);

	//description: Less than comparison - Compare the string length of of each FindFault indexes holding an EW object.
	//			   Default array size is 5, so whichever object has 3 or more longer strings will be the greater object.
	//			   Return true or false.
	//pre: Both FindFault objects may or may not be corrupted
	//post: No change to state
	bool operator < (const FindFault &);

	//description: Compare the size of the string in EncryptWord in each FindFault indexes. Every index has to pass the test
	//			   in order for the condition to be true.
	//pre: Both FindFault objects may or may not be corrupted
	//post: No change to state
	bool operator == (const FindFault &);

	//description: Compare the size of the string in EncryptWord in each FindFault indexes. If one index fails the test 
	//			   method will return true.
	//pre: Both FindFault objects may or may not be corrupted
	//post: No change to state
	bool operator != (const FindFault &);


private:
	//description: Counts the number of words being corrupted and will be called by faultQuery() to return the stat
	int statistics();

	//description: This method corrupts the array of words passed in by the client class. Is called by the callEncrypt() method
	string * corruption(string[]); //Maybe make public and corrupt it then

								   //description: Calls by FindFault constructor for the EncryptWord class to encrypt and decrypt array accordingly.
								   //has-a relationship with FindFault
	EncryptWord ew[ARRAY_SIZE];

	int numOfQuery; //Count the number of corrupted words

	string listOfOriginalWords[ARRAY_SIZE]; //holds the orginal word, might not change array size so won't need to use dynamic array

	bool stateOfCorrupt; //set to false as the FindFault is being created, changes to true when words get corrupted. 

};


#endif
