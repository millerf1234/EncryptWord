// AUTHOR: Forrest Miller
// FILENAME: P1.cpp
// DATE: September 28, 2017
// PLATFORM: Macbook Pro Late 2012 running OS 10.12.6, IDE: xcode
// REVISION HISTORY:
//      10/3/2017 Rewrote Driver to conform more to assignment specs
//      10/10/2017 Rewrote Driver after receiving comments on HW1

/*
 Driver Overview:
     This driver is designed to test the functionality of the EncryptWord object
 
     This driver is composed of 2 parts, the first is an automated process where
       a bunch of the objects methods are called with their output being printed
       to the console screen. A lot of these tests are done using randomly
       generated words with shifts of random length. In order to have multiple
       EncryptWord objects existing at the same time, a vector storage container
       is used to hold and keep track of the objects.
 
     The second part of this driver consists of a user-input-required guessing
       game where the user is expected to enter their own words to be encoded,
       and to then have to guess what shift was used to encode their word.
       The driver will reprompt the user if invalid input is entered or if
       the word entered fails to meet the length requirement. The user is also
       given the option to keep repeating the program once they have guess the
       correct shift to encode the word.
       Pleast note that there are multiple answers for the shift because both
       positive and negative numbers are accepted and there is no restiction on
       guess size (aside from the storage limitations of integers).
 
 Source of Input:
     The user is expected to be able to type input into the program for it to
     function properly. std::cin is used to get input from the keyboard.
 
 Output:
     printing to the screen is handled with std::cout. Some of the longer
     strings to be printed are constructed with ostringstreams.
 
 Note regarding Design:
     This driver was designed using a by-contract philosphy, so care was taken
     to ensure it follows all of the proper pre- and post-conditions described
     within the EncryptWord's class documentation.
 
 Intent:
     The intent of this driver is to demonstrate the complete and correct
     function of the EncryptWord object class.
*/

#include <iostream>
#include <stdint.h> //This is a safety to ensure my code will compile
#include <sstream> //Used to build strings
#include "EncryptWord.h"
#include <vector>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define EXIT_SUCCESS 0
#define INDEX_SHIFT 1  //Used for array index conversions
#define CAP_Z 90 //Value of capital Z
#define CAP_A 65 //char value of capital A
#define LC_Z 122 //char value of lower case z
#define LC_A 97 //char value of lower case a

using std::cout; //No need for the entire namespace

//Constants
const int LETTERS_IN_ALPHABET = 26;
const int SHORTESTPOSSIBLEWORDLENGTH = 4;


const uint8_t A = 65; //uint8_t is treated as a character

//Here are some test strings to be encoded
//Upper case alphabet
const std::string ALPHABET_UC = "ABCDEFGHIJKLMONPQRSTUVWXYZ";
//Alphabet of both upper and lower case
const std::string FULL_ALPHABET = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUu"
"VvWwXxYyZz";

//Function Prototypes
void printWelcome(void); //Prints welcome message to console screen
void doSelfTest(void); //Runs selfTest
void doUserInteractiveTest(void);
void printFarewell(void); //Prints goodbye message to console screen
void printWordInfo(EncryptWord&); //Prints to screen an EcryptWord object
std::string generateRandomString(int length);//generates random strings

int main(int argc, const char * argv[]) {
    //First, set a new random seed
    srand((uint)time(NULL));
    printWelcome(); //Print Welcome Message to User
    //Run Self-Test Procedure
    doSelfTest();
    //Do part 2, the User-interactive test
    doUserInteractiveTest();
    //Print goodbye message
    printFarewell();
    return EXIT_SUCCESS;
}

//Don't call with length < 1
std::string generateRandomString(int length) {
    char buffer[length + INDEX_SHIFT];
    for (int i = 0; i < length; i++) {
        buffer[i] = A + rand() % LETTERS_IN_ALPHABET;
    }
    buffer[length] = NULL; //Need to terminate the cstring with NULL
    return buffer;
}

void printWelcome(void) {
    //std::ostringstream oss;
    cout << "Welcome to the Encrypt Word Test Driver!\n"
    << "This program is designed to test the functionality of the EncryptWord "
    << "object.\n\nThis driver operates in two parts, the first is an automated"
    << " self-test routine, while the second part is user-interactive.\n\n"
    << std::endl;
    cout << "Press Enter to commence self-test (enter) ";
    std::cin.get();
    cout << "\nCommencing with the self-testing procedure...\n";
    cout << std::endl;
}

//Self-test runs some automated processesses and prints our their results to the
//screen. A lot of these processesses involve random number generation. The
//alphabet is used as a test word for calibration purposes.
void doSelfTest(void) {
    //Test 1 -- Alphabet Test
    EncryptWord alphabet(ALPHABET_UC, 0);
    cout << "TEST 1 -- Alphabet Test\nString to be used for test: "
    << ALPHABET_UC << std::endl;
    cout << "EncryptWord object successfully created with shift of 0.\n"
    << "Result of getState(): " << alphabet.getState()
    << "\nResult of getWord(): " << alphabet.getWord()
    << "\nResult of getShift(): " << alphabet.getShift()
    << "\nResult of getStatistics:" << std::endl
    << alphabet.getStatistics() << std::endl;
    cout << "Testing method reset(). State is now: ";
    alphabet.reset();
    cout << alphabet.getState() << std::endl << std::endl;
    cout << "Word stored within this object should not have changed because the"
    << "\nshift was 0. Here is the word currently stored within this object:\n"
    << alphabet.getWord();
    cout << "\n\nTime for the full alphabet test!" << std::endl;
    
    cout << "Creating an encryptword object with the string: \n" <<
    FULL_ALPHABET;
    
    EncryptWord fullAlpha (FULL_ALPHABET);
    cout << "Object created with state: " << fullAlpha.getState() << " and with"
    << "shift: " << fullAlpha.getShift() << std::endl;
    
    
    //Test 2 -- Creating A Bunch of Objects at Once
    cout << std::endl << std::endl << std::endl;
    cout << "TEST 2 -- Creating a bunch of EncryptWord Objects at once\n"
    << std::endl;
    cout << "For this test, a bunch of seperate EncryptWord object will be "
    << "created and\nstored within a vector. Each word will be randomly "
    << "generated.\n" << std::endl;
    cout << "Generating a vector of encrypted words...\n";
    std::string s;
    std::vector<EncryptWord> wordHolder;
    
    for (int i = SHORTESTPOSSIBLEWORDLENGTH; i < LETTERS_IN_ALPHABET; i++) {
        s = generateRandomString(i);
        cout <<"Creating EncryptWord for string: " << s << "." << std::endl;
        EncryptWord word = EncryptWord(s);
        wordHolder.push_back(word);
        //cout << "EncryptedWord is: " << word.getEncryptedWord() << std::endl;
        printWordInfo(word);
    }
}

void doUserInteractiveTest(void) {
    cout << "\n\n\n\n\nTime for the interactive part of the driver\n";
    
    bool guessIsCorrect = false;
    bool repeat = true;
    bool inputValid = false;
    EncryptWord* wrd = nullptr;
    std::string s;
    uint8_t c;
    while (repeat) {
        while (!inputValid) {
            inputValid = true;
            cout << "Enter a word to have encoded, you will then get to guess"
            "what\nthe shift value that encodes your word is." << std::endl;
            cout << "(Word should be 4 characters or more in length)\n";
            cout << "Enter word: ";
            std::cin >> s;
            //check to make sure input consists entirely of letters
            for (int i = 0; i < s.length() && inputValid; i++) {
                c = (uint8_t)s.at(i);
                //if character is not a letter
                if (!((c >= CAP_A && c <= CAP_Z) || (c >= LC_A && c <= LC_Z))){
                    cout << "\n\nOops, you word contained characters besides "
                    "alphabetical letters. Here is what you entered: \n"
                    << s << "\nPlease try again" << std::endl << std::endl;
                    inputValid = false;
                }
            }
            //if input is valid
            if (inputValid) {
                wrd = new EncryptWord(s);
                //check to see if word was created successfully
                if (!wrd->getState()){
                    inputValid = false;
                    cout << "\nOOPS! You input was too short.\nPlease make sure"
                    " your word is at least 4 charaters in length.\n"
                    "Please try again" << std::endl;
                    delete wrd;
                    wrd = nullptr;
                }
            }
        }
        if (wrd != nullptr) {
            cout << "\nWord successfully encrypted. Here is the result of the "
            "encryption: \n" << wrd->getWord() << "\n";
            
            while (!guessIsCorrect) {
                int i;
                cout << "Word you entered: " << s << "     EncryptedWord: "
                << wrd->getWord() << "." << std::endl;
                cout << "Enter a guess as to what the shift for the word is: ";
                std::cin >> i;
                guessIsCorrect = wrd->verifyShift(i);
                if (!guessIsCorrect) {
                    cout << "OOPS, your guess was incorrect. Here are your "
                    "guess statistics: ";
                    cout << wrd->getStatistics();
                    
                    std::cin.get();
                }
                else {
                    cout << "CONGRATULATIONS!!! YOU GUESSED CORRECTLY!"
                    << "\nShift Used: " << wrd->getShift()
                    << "\nYour Guess: " << i << std::endl
                    << "Here are your guess statistics: ";
                    cout << wrd->getStatistics();;
                }
            }
            delete wrd;
        }
        std::cin.get();
        cout << "\nWould you like to enter another word to encrypt? [y/n]";
        std::cin >> s;
        if (s.at(0) == 'y' || s.at(0) == 'Y') {
            repeat = true;
            inputValid = false;
            guessIsCorrect = false;
        }
        else {
            repeat = false;
        }
    }
}
    
void printWordInfo(EncryptWord& wordToPrint) {
    std::ostringstream oss; //stringStream to build the string
    if (!wordToPrint.getState()) { //If word's state is false, then only print
        cout << "State: False" << std::endl; //its state
    }
    else {
        oss <<"Stored Word: " << wordToPrint.getWord() << "\n";
        oss << "Shift: " << wordToPrint.getShift() << "| State: True";
        oss << "| Statistics for this word:\n" << wordToPrint.getStatistics();
        cout << oss.str();
    }
}

void printFarewell(void) {
    cout << "\nThis concludes our testing. Goodbye!" << std::endl;
}
