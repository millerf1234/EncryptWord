//
//  main.cpp
//  millerf_p2
//
//  Created by Forrest Miller on 10/16/17.
//  Copyright © 2017 Forrest Miller. All rights reserved.
//

#include <iostream>
//#include "EncryptWord.h" //This is brought in by FindFault so don't need to
//                           include it twice
#include <stdint.h> //This is a safety to ensure my code will compile
#include "FindFault.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define EXIT_SUCCESS 0

using std::cout;
using std::endl;
using std::cin;

//Driver function Prototypes:
void printWelcomeMsg(void); //Prints Welcome Message
void printGoodbyeMsg(void); //Prints Goodbye Message
void runSelfDiagnosticsTest(void); //Runs a self-test
void runUserInteractiveTest(void); //Runs the user-interactive test
std::string generateRandomString(int length);//generates random strings

//Constants
const uint8_t A = 65; //uint8_t is treated as a character
//const uint8_t CAP_Z = 90u; //Character value of uppercase Z
//const uint8_t CAP_A = 65u; //Character value of uppercase A
//const uint8_t LC_Z = 122u; //Character value of lowercase z
//const uint8_t LC_A = 97u; //Character value of lowercase a
const int LETTERS_IN_ALPHABET = 26; //26 letters in the English Alphabet
const int INDEX_SHIFT = 1; //Used to convert array indexing


int main(int argc, const char * argv[]) {
    //Set Random Seed
    srand((uint)time(NULL));
    //Print welcome message
    printWelcomeMsg();
    //Run the self-diagnostics test
    runSelfDiagnosticsTest();
    //Run the user-interactive test
    runUserInteractiveTest();
    
    printGoodbyeMsg();
    return EXIT_SUCCESS;
}


void printWelcomeMsg(void) {
    cout << "Hello! Welcome to the FindFault test driver program. " << endl;
    cout << "The first part of this driver will consist of a self-diagnostic"
            " test, while the\nsecond part will be user interactive.\n\n(Press"
            " ENTER to run the self-test)" << endl;
    cin.get();
}

void printGoodbyeMsg(void) {
    cout << "\nThank you for using the FindFault test driver program. Goodbye!";
    cout << endl;
}

void runSelfDiagnosticsTest(void) {
    bool* arrayOfFaults;
    //selftest strings to use
    string testStr = "FIRST second THIRD fourth FIFTH sixth SEVENTH eighth "
                     "NINETH tenth"; //Used in test1
    //Test 1
    cout << "\n\nCommencing Self-Diagnostic test...\n     TEST_1\n";
    cout << "Creating FindFault object with string: \n\"" << testStr << "\"\n";
    FindFault tst1(testStr);
    cout <<"FindFault object successfuly created. Here is result of encrytion:";
    cout << endl << tst1.getEncryptedWords() << endl;
    
    cout << "\nFaults occured during encoding: ";
    if (tst1.getHasFaults() ) {
        cout << "True" << endl;
        cout << "Number of faults: " << tst1.findNumberOfFaults() << endl;
        cout << "Shift that was supposed to be used for encryption: ";
        cout << tst1.getShift() << endl;
        cout << "Shift that was used to encrypt corrupted words: ";
        cout << tst1.findCorruptedEncryption() << endl << endl;
        
        cout << "Location of faults (a location of 1 means fault in first word"
                ", 2 means fault in\nsecond word, etc...)\n";
        arrayOfFaults = tst1.findCorruptedLocations();
        if (arrayOfFaults != nullptr) {
            for (int i = 0; i < tst1.getNumberOfWords(); ++i) {
                if (arrayOfFaults[i] != false) {
                    //Index shift makes array position 0 equal to the first word
                    cout << (i + INDEX_SHIFT) << " ";
                }
            }
            cout << endl;
        }
        
        else {
            cout << "Uh-oh, for some reason the fault array has a null-ptr, ";
            cout << "which should never be the case.";
            cout << endl << "Self-Test failed!!!!";
        }
        cout << "\nNumber of queries made on locating faults since object ";
        cout << "creation: ";
        cout << tst1.getStatistics();
    }
    else {
        cout << "False" << endl;
        cout << "Number of queries made on locating faults since object ";
        cout << "creation: ";
        cout << tst1.getStatistics();
    }
    
    cout << "\n     End TEST_1" << endl;
    
    //TEST2
    string testStr2 = "This STrinG COntaiNS A MIXTURe oF LoWer And UpPEr CasE"
    " ChARAcTeRs";
    cout << endl << endl << endl << "     TEST_2" << endl;
    cout << "In this test, a string is used containing words that do not meet "
    "the length\nrequirement.";
    cout << " These words should be ignored during the encryption process.";
    cout << "\nHere is the string that is being passed to the constructor:\n";
    cout << "\"" << testStr2 << "\"";
    
    cout << "\n\nCreating object with specified string... DONE\n";
    FindFault tst2(testStr2);
    cout << "FindFault object successfully created. Here is result of ";
    cout << "encrytion:";
    cout << endl << tst2.getEncryptedWords() << endl;
    
    cout << "\nFaults occured during encoding: ";
    if (tst2.getHasFaults() ) {
        cout << "True" << endl;
        cout << "Number of faults: " << tst2.findNumberOfFaults() << endl;
        cout << "Shift that was supposed to be used for encryption: ";
        cout << tst2.getShift() << endl;
        cout << "Shift that was used to encrypt corrupted words: ";
        cout << tst2.findCorruptedEncryption() << endl << endl;
        
        cout << "Location of faults (a location of 1 means fault in first word"
        ", 2 means fault in\nsecond word, etc...)\n";
        arrayOfFaults = tst2.findCorruptedLocations();
        if (arrayOfFaults != nullptr) {
            for (int i = 0; i < tst2.getNumberOfWords(); ++i) {
                if (arrayOfFaults[i] != false) {
                    //Index shift makes array position 0 equal to the first word
                    cout << (i + INDEX_SHIFT) << " ";
                }
            }
            cout << endl;
        }
        else {
            cout << "Uh-oh, for some reason the fault array has a null-ptr, ";
            cout << "which should never be the case. Within test2\n";
            cout << endl << "Self-Test failed!!!!";
        }
        cout << "\nNumber of queries made on locating faults since object ";
        cout << "creation: ";
        cout << tst2.getStatistics();
    }
    else {
        cout << "False" << endl;
        cout << "Number of queries made on locating faults since object ";
        cout << "creation: ";
        cout << tst2.getStatistics();
    }
    
    cout << "\n     End TEST_2" << endl;
    
    
    //TEST3
    cout << endl << endl << endl << "     TEST_3" << endl;
    cout << "This test will be a little different from the other tests.\n";
    cout << "In this test, a random number of randomly generated strings of ";
    cout << "random length will\nbe fed into a FindFault object.";
    
    cout << endl << endl << "THE REST OF TEST_3 WILL BE IMPLEMENTED AT A LATER"
                            " DATE!\n";
    
}

void runUserInteractiveTest(void) {
    //Currently does diddly-squat
}

//Don't call with length < 1
//std::string generateRandomString(int length) {
//    char buffer[length + INDEX_SHIFT];
//    for (int i = 0; i < length; i++) {
//        buffer[i] = A + rand() % LETTERS_IN_ALPHABET;
//   }
//    buffer[length] = NULL; //Need to terminate the cstring with NULL
//    return buffer;
//}
