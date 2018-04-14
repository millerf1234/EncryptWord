// Author: Forrest Miller
// Filename: EncryptWord.h
// Date: September 28, 2017
// Version: 1.0
//
//
//      Class Overview:
//          This .cpp file contains the implementation for the EncryptWordclass.
//          This class features two constructors, a destructor, getter methods
//          for accessing its class member data, and a member function for
//          allowing guesses to be made as to it's currently active shift.
//
//          The constructors for this class need to have input words be at least
//          4 characters in length, any word shorter than this will cause the
//          objects to be constructed in an invalid state (which can be tracked
//          using the member boolean variable 'state')
//
//        DATA PROCESSED:
//          This class is designed to work on strings, and as such each
//            constructor for it requires as a minimum a string as input.
//          This object also stores integers for the shift values. Character
//            arithmatic when handling the ciphering/deciphering of the strings
//            are done using uint8_t type variables to perform the arithmatic.
//            C++ treats uint8_t's as characters.
//
//
// Assumptions:
//      It is assumed that anyone who uses this class will read all the
//        documentation because a lot of these methods do not have safety checks
//        built into them and thus using them in ways they are not intended to
//        be used will cause undocumented/incorrect behavior.
//
//     It is assumed that the string inputs for this class will only contain
//        alphabetical characters, and as such any other characters that are not
//        alphabetical will not be shifted/unshifted corretly.
//
//
//   Implementation Invariants:
//        Input strings should only contain alphabetical characters,
//          no punctuation, spaces or special characters
//        Input Strings should be 4 or more characters in length
//        Avarage Guesses are tracked using a float, so it is assumed that this
//          will provide enough decimal-places of precision to allow the user to
//          get a good feel for the number of guesses they have made
//        Since shifts can be randomly generated, it is assumed the randomly
//          generated shifts will always be a positive integer value between 0
//          and 25. It is also assumed shifts that differ by a multiple of 26
//          are equal (ie that 0=26, -1=25, -2=24, 26=52, etc...)
//


#include "EncryptWord.h"
#include <stdint.h>
#include <iostream>
#include <sstream> //Used to build a string for the guess statistics

#define LETTERS_IN_ALPHABET 26
#define MINIMUM_WORD_SIZE 4
#define CAP_Z 90 //Value of capital Z
#define CAP_A 65 //char value of capital A
#define LC_Z 122 //char value of lower case z
#define LC_A 97 //char value of lower case a
#define STRING_LENGTH_OF_CHAR 1 //A character has length of 1

//Constructor
EncryptWord::EncryptWord(std::string inputWord) {
    this->shift = rand() % LETTERS_IN_ALPHABET;
    this->numOfGuesses = 0;
    this->highestGuess = 0;
    this->lowestGuess = 0;
    this->sumOfGuesses = 0;
    //this->averageGuessValue = 0.0f;
    this->state = true;
    if (!checkLengthRequirement(inputWord)) {
        this->state = false;
        this->word = "";
    }
    else {
        this->word = performCipherShift(inputWord);
    }
}

//Alternate Constructor
EncryptWord::EncryptWord(std::string inputWord, int shift) {
    this->shift = shift % LETTERS_IN_ALPHABET; //shift in interval 0-25
    this->numOfGuesses = 0;
    this->highestGuess = 0;
    this->lowestGuess = 0;
    this->sumOfGuesses = 0;
    //this->averageGuessValue = 0.0f;
    this->state = true;
    if (!checkLengthRequirement(inputWord)) {
        this->state = false;
        this->word = "";
    }
    else {
        this->word = performCipherShift(inputWord);
    }
}

// Destructor
EncryptWord::~EncryptWord(void) {
    //Nothing to do here
}

std::string EncryptWord::getWord() const {
    return this->word;
}

std::string EncryptWord::getEncryptedWord(void) const {
    std::string s = this->word;
    return s;
}

std::string EncryptWord::getDecodedWord(void) {
    std::string s = this->word;
    return undoCipherShift(s);
}

bool EncryptWord::getState(void) const {
    return this->state;
}

int EncryptWord::getShift(void) const {
    return this->shift;
}

void EncryptWord::reset(void) {
    if (this->state) { //If the shift is currently turned on
        this->state = !this->state; //flip the state
        this->word = undoCipherShift(this->word);
    }
    else { //If the shift is currently turned off
        this->state = !this->state;
        this->word = performCipherShift(this->word);
    }
}

std::string EncryptWord::getStatistics(void) const {
    std::ostringstream oss; //stringStream to build the string
    if (this->numOfGuesses == 0) {
        oss << "# of guesses = " << this->numOfGuesses << " | "
        << "Highest guess = " << "N/A" << " | "
        << "Lowest guess = " << "N/A" << "   "
        << "\nAverage guess = " << getAvarageGuess() << std::endl;
    }
    else {
        oss << "# of guesses = " << this->numOfGuesses << " | "
        << "Highest guess = " << this->highestGuess << " | "
        << "Lowest guess = " << this->lowestGuess << "   "
        << "\nAverage guess = " << getAvarageGuess() << std::endl;
    }
    std::string s = oss.str();
    return s;
}

bool EncryptWord::verifyShift(int shiftGuess) {
    int guessVal = shiftGuess;
    if (shiftGuess < 0) {
        guessVal = shiftGuess % LETTERS_IN_ALPHABET;
        guessVal += LETTERS_IN_ALPHABET ;
    }
    addValueToGuesses(shiftGuess);
    if (guessVal % LETTERS_IN_ALPHABET == this->shift) {
        return true;
    }
    return false;
}

bool EncryptWord::checkLengthRequirement(std::string const& wordToTest) {
    if (wordToTest.length() < MINIMUM_WORD_SIZE) {
        return false;
    }
    return true;
}

std::string& EncryptWord::performCipherShift(std::string & word) {
    long lengthOfWord = word.length();
    uint8_t stringIterator;
    for (int i = 0; i < lengthOfWord; i++) {
        stringIterator = (uint8_t)word.at(i);
        if (stringIterator <= CAP_Z){ //If character is a capital letter
            stringIterator = (stringIterator + (uint8_t)this->shift);
            if (stringIterator > CAP_Z) {
                stringIterator -= LETTERS_IN_ALPHABET;
            }
            else if (stringIterator < CAP_A) {
                stringIterator += LETTERS_IN_ALPHABET;
            }
        }
        else { //if character is a lowercase letter
            stringIterator = (stringIterator + this->shift);
            if (stringIterator > LC_Z) {
                stringIterator -= LETTERS_IN_ALPHABET;
            }
            else if (stringIterator < LC_A) {
                stringIterator += LETTERS_IN_ALPHABET;
            }
        }
        //Replace String at position i with updated chararcter
        word.replace(i, STRING_LENGTH_OF_CHAR, STRING_LENGTH_OF_CHAR,
                     stringIterator);
    }
    return word;
}

std::string& EncryptWord::undoCipherShift(std::string & word) {
    long lengthOfWord = word.length();
    uint8_t stringIterator;
    for (int i = 0; i < lengthOfWord; i++) {
        stringIterator = (uint8_t)word.at(i);
        if (stringIterator <= CAP_Z){ //Check to see if character is capitalized
            stringIterator = (stringIterator - this->shift);
            if (stringIterator > CAP_Z) {
                stringIterator -= LETTERS_IN_ALPHABET;
            }
            else if (stringIterator < CAP_A) {
                stringIterator += LETTERS_IN_ALPHABET;
            }
        }
        else { //character must then be lowercase
            stringIterator = (stringIterator - this->shift);
            if (stringIterator > LC_Z) {
                stringIterator -= LETTERS_IN_ALPHABET;
            }
            else if (stringIterator < LC_A) {
                stringIterator += LETTERS_IN_ALPHABET;
            }
        }
        //Replace String at position i with updated chararcter
        word.replace(i, STRING_LENGTH_OF_CHAR, STRING_LENGTH_OF_CHAR,
                     stringIterator);
    }
    return word;
}

float EncryptWord::getAvarageGuess(void) const {
    if (numOfGuesses == 0) {
        return 0.0f;
    }
    return (float)(this->sumOfGuesses / this->numOfGuesses);
}

//addValueToGuesses handles updating the objects guess statistics
void EncryptWord::addValueToGuesses(int value) {
    //If this is the first guess to be made
    if (this->numOfGuesses == 0) {
        this->numOfGuesses++;
        this->lowestGuess = value;
        this->highestGuess = value;
        this->sumOfGuesses = value;
        //this->averageGuessValue = (float) value;
    }
    else { //if previous guesses have already been made
        this->numOfGuesses++;
        this->sumOfGuesses += value;
        if (this->lowestGuess > value) {
            this->lowestGuess = value;
        }
        if  (this->highestGuess < value) {
            this->highestGuess = value;
        }
        //this->averageGuessValue = ((float)sumOfGuesses/(float)numOfGuesses);
    }
}



