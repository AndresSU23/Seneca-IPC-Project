/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : David Andres Sanchez Umbarila
Student ID#: 140273228
Email      : dasanchez-umbarila@myseneca.ca
Section    : NBB

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#define MAX_PHONE_SIZE 10

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
/**
 * Guarantees an integer value is entered and returned.
 * @return An integer value inputted by the user.
*/
int inputInt();

/**
 * Guarantees a positive integer value is entered and returned.
 * @return A positive integer value inputted by the user.
*/
int inputIntPositive();

/**
 * Guarantees an integer value is entered within the range (inclusive) and returned.
 * @param intLower An integer number represents the lower-bound of the permitted range.
 * @param intUpper An integer number represents the upper-bound of the permitted range.
 * @return A integer value inputted by the user that belongs inclusively within the 
 * given range
*/
int inputIntRange(int, int);

/**
 * Guarantee a single character value is entered within the list of valid characters 
 * (as defined by the C string argument received) and returned.
 * @param validChars An unmodifiable C string array representing a list of valid characters.
 * @return A char character inputted by the user that belongs in the given valid character
 * array.
*/
char inputCharOption(const char[]);

/**
 * Obtains user input for a C string value with a length 
 * (number of characters) in the character range specified by the charMin and charMax 
 * arguments received (inclusive).
 * @param stringPointer A character pointer representing a C string
 * @param charMin An integral value of the minimum number of characters the 
 * user-entered value must be.
 * @param charMax an integral value of the maximum number of characters the 
 * user-entered value can be.
 * @return Does not return a value, but does return a C string via the stringPointer argument 
 * parameter pointer.
*/
void inputCString(char *, int, int);

/**
 * Display an array of 10-character digits as a formatted phone number.
 * @param phoneNumber An unmodifiable character pointer representing a C string
*/
void displayFormattedPhone(const char[]);
// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
