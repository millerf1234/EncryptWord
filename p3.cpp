// Author: Forrest Miller
// Filename: p3.cpp
// Date: November 5, 2017
// Version: 1.0
//

#include <iostream>
#include <stdint.h> //This is to ensure my code will compile with uint8_t's
#include "FindFault.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */

using std::cout;
using std::endl;


// Description: This driver performs a self-test by testing each of the newly
//              added operators in version 1.1 of this class and compares the
//              results with the expected results.
//
// Explanation of UI: There is no UI, so just sit back and let the driver do
//                    its thing.
//
// Assumptions: This driver is assumed to be used with the FindFault and
//              EncryptWord classes to test their functionality.
//
// Intent of this driver: This driver is intended to demonstrate correct
//                        functionality of the FindFault and EncryptWord classes
//
// Structure of this driver: This driver is designed to automatically just do
//                            its thing when run, no input from the user is
//                            required.
//                            The driver will first do a test of EncryptWord,
//                            followed by a test of FindFault. The focus of this
//                            driver will be constrained to the additions made
//                            in version 1.1 of each class.



//Driver function Prototypes:
void printWelcomeMsg(void); //Prints Welcome Message
void printGoodbyeMsg(void); //Prints Goodbye Message

void runSelfDiagnosticsTest(void); //Runs a self-test
//void runUserInteractiveTest(void); //Runs the user-interactive test
std::string generateRandomString(int length);//generates random strings


//Constants
//const uint8_t CAP_Z = 90u; //Character value of uppercase Z
const int CAP_A = 65u; //Character value of uppercase A
//const uint8_t LC_Z = 122u; //Character value of lowercase z
//const uint8_t LC_A = 97u; //Character value of lowercase a
const int LETTERS_IN_ALPHABET = 26; //26 letters in the English Alphabet
//const int INDEX_SHIFT = 1; //Used to convert array indexing


int main(int argc, const char * argv[]) {
    
    //Set Random Seed
    srand((uint)time(NULL));
    //Print welcome message
    printWelcomeMsg();
    //Run the self-diagnostics test
    runSelfDiagnosticsTest();
    //Run the user-interactive test
    //  runUserInteractiveTest(); //Never implemented
    
    printGoodbyeMsg();
    
    return EXIT_SUCCESS;
}

void printWelcomeMsg(void) {
    cout << "Hello! Welcome to the FindFault and Encrypt Word"
    " test driver program. " << endl;
    cout << "This driver consists entirely of a self-diagnostic"
            " test algorithm, which will now begin running." << endl;
}

void printGoodbyeMsg(void) {
    cout << "\nThank you for using the FindFault test driver program. Goodbye!";
    cout << endl;
}

void runSelfDiagnosticsTest(void) {
    cout << "\n\nCommencing Test of EncryptWord operators...\n";
    cout << "Creating EncryptWord with word \"cats\" and a random"
    " encryption shift... Done!\n";
    EncryptWord cats("cats");
    cout << "Here is the object that was created: \n" << cats;
    cout << "\nNow creating a second EncryptWord object with the word \"dogs\"";
    EncryptWord dogs("dogs");
    cout << "... Done!\nHere is the object that was created: \n" << dogs;
    cout << "\nNow creating a copy of the EncryptWord \"cats\"...";
    EncryptWord catsCopy(cats);
    cout << "Done!\nHere is the result of the copy:\n" << catsCopy;
    cout << "Now testing the operator== by seeing if \"cats\" and \"catscopy\""
    " are equal.\nIf they are equal, the result will be 1.\nThe result is: "
    << (cats == catsCopy) << endl;
    cout << "Now testing operator== with \"cats\" and \"dogs\". Result should"
    " be 0.\nThe result is: " << (cats == dogs) << endl;
    cout << "\nNow testing the operator!= by seeing if \"cats\" and \"catscopy"
    "\" are equal.\nIf they are not equal, the result will be 0.\nThe result is"
    ": " << (cats != catsCopy) << endl;
    cout << "Now testing operator!= with \"cats\" and \"dogs\". Result should"
    " be 1.\nThe result is: " << (cats != dogs) << endl;
    cout << "\n\nNow to test the operator+= by concatinating the string \"Are"
    "Awesome\" to the end\nof our object \"cats\"";
    cout << "\nHere we go...\n";
    cats += "AreAwesome";
    cout << "DONE! Here is the result\n" << cats;
    cout << "Just to check, \"cats\" should no longer be equal to \"catsCopy\"";
    cout << endl << "Result of cats == catsCopy should be 0. Result is: "
    << (cats == catsCopy) << endl;
    cout << "\nJust for good measure, here is result of cats != catsCopy: ";
    cout << (cats != catsCopy) << endl;
    
    cout << "Let's now test the assigment operator by setting catsCopy to cats";
    catsCopy = cats;
    cout << endl << "DONE! Here is cats:\n" << cats << endl << "And here is "
    "catsCopy:\n" << catsCopy;
    
    cout << "\n\nNow to test whether numbers with shifts that differ by 26 "
    "evaluate as equal.\n";
    cout << "Creating EncryptWord object \"negTest\" with a shift of -27";
    EncryptWord negTest ("AAAAA", -27);

    cout << "Here is negTest:" << negTest << endl;
    EncryptWord identical ("AAAAA", -1);
    cout << "Here is an object that should identify as identical to \"negTest\""
    ",\nlet's call it \"identical.\"\n";
    cout << "Here is \"identical:\"\n" << identical;
    cout <<"\nLet's create a third identical object called \"alsoIdentical\"\n";
    cout << "Here is \"alsoIdentical:\"\n";
    EncryptWord alsoIdntical ("AAAAA", 25);
    cout << alsoIdntical;
    cout << "\n\nTime to test our comparison operators:\n\n";
    cout << "negTest == identical:  " << (negTest == identical) << endl;
    cout << "negTest == alsoIdntical:  " << (negTest == alsoIdntical) << endl;
    cout << "alsoIdntical == identical:  " << (alsoIdntical == identical)<<endl;
    
    cout << "negTest != identical:  " << (negTest != identical) << endl;
    cout << "negTest != alsoIdntical:  " << (negTest != alsoIdntical) << endl;
    cout << "alsoIdntical != identical:  " << (alsoIdntical != identical)<<endl;
    
    cout << "\nHere is negTest:\n" << negTest;
    
    cout << endl;
    cout << "-----------------------------------------------------------------";
    cout << endl << "This concludes out EncryptWord Testing" << endl;
    cout << "-----------------------------------------------------------------";
    cout << endl << endl << endl;
    
    cout << "Time for FindFault operator testing: \n\n";
    cout << "Creating a FindFault object from the string \"Fish COWS\"\n";
    FindFault fshCow("Fish COWS");
    cout << "DONE! Here is the result: " << endl;
    cout << fshCow;
    
    cout << "\n\nNow to test what happens if we append our EncryptWord object "
    "\"dogs\" to the\nend of FishCOWS...\nDONE!\n";
    fshCow += dogs;
    cout << "Here is the new FishCOWS: \n" << fshCow;
    
}
/*
void runUserInteractiveTest(void) {
    
}
*/

//Don't call with length < 1
std::string generateRandomString(int length) {
    string s = "";
    //char randomLetter;
    for (int i = 0; i < length; i++) {
        s += (CAP_A + rand() % LETTERS_IN_ALPHABET);
     }
    return s;
}



