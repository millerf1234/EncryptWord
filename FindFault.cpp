// Author: Forrest Miller
// Filename: FindFault.cpp
// Date: November 5, 2017
// Version: 1.0 October 24, 2017
//          1.1 Novermber 5, 2017 -- Added overloaded operators
// References: I used this link to understand syntax and implementation of
//             Move operator:
//             https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)

#include "FindFault.h"

using std::string;
//
// Description: see header file
//
//      Class Overview:
//              This .cpp files contains the implementation for the FindFault
//                  class. This class features three constructors plus a copy
//                  constructor, a copy assignment operator and a move
//                  assignment operator. Hopefully having these implemented will
//                  decrease the likelyhood of memoryleaks.
//              The findCorruptedLocations method requires a boolean array be
//                  passed to it as a parameter so as to not cause a potential
//                  memory leak by calling new inside a member function. There
//                  is a try-catch block inside this function so as to prevent
//                  a runtime exception if the passed array is not large enough.
//      DATA PROCESSED:
//              This class is designed to operate on a string containing only
//                  upper- and lower-case letters seperated by blank whitespace.
//                  Sequences of four or more consecutive letters in the string
//                  will be encoded using a randomly generated or user-specified
//                  shift.
//
// CLASS INVARIANTS -- see header file
// IMPLEMENTATION INVARIANTS:
// Assumptions:
//             It is assumed all strings passed in to constructors will contain
//               only upper/lower case letters and spaces.
//             It is assumed each word will be seperated by a space
//             It is assumed that words are supposed to all receive the same
//               encryption, but that corruption will occur by a word receiving
//               a different encryption. All errors will occur in the same way.
//             It is assumed that strings passed in will not end with a space,
//               so a space is manually added to the end of each string to
//               ensure that the last word is encoded
//             The destructor here will handle deleting all memory allocated, so
//               there is no need to call delete outside of this class.
//

//--------------------------------------------------------------------
//    Constants
//--------------------------------------------------------------------
const char SPACE = ' ';
const int MIN_WORD_LENGTH = 4;
const int LETTERS_IN_ALPHABET = 26;
const int CORRUPTION_CHANCE_DENOMINATOR = 5; //Chance of corruption
//    i.e. a value of 5 gives 1/5 chance of corrupted encryption per word
const int CORRUPTION_SHIFT_RANGE_MAX = 25;
const int CORRUPTION_SHIFT_RANGE_MIN = 1;
const int INDEX_SHIFT = 1;

//--------------------------------------------------------------------
//    Constructors
//--------------------------------------------------------------------
FindFault::FindFault() {
    initialize();
}

FindFault::FindFault(const string& words) {
    initialize();
    this->shift = rand() % LETTERS_IN_ALPHABET; //Set shift to a random value
    parseInputIntoArray(words);
}

FindFault::FindFault(const string& words, int encodingShiftToUse) {
    initialize();
    this->shift = encodingShiftToUse;
    parseInputIntoArray(words);
}

//copy constructor
FindFault::FindFault(const FindFault &ff2) {
    initialize();
    this->shift = ff2.shift;
    this->numOfWords = ff2.numOfWords;
    this->faultQueries = ff2.getStatistics();
    if (ff2.encryptedWords) {
        this->encryptedWords = new EncryptWord[(unsigned long)this->numOfWords];
        //copy array
        for (int i = 0; i < numOfWords; i++) {
            this->encryptedWords[i] = ff2.encryptedWords[i];
        }
    }
}

//--------------------------------------------------------------------
//    Destructor
//--------------------------------------------------------------------
FindFault::~FindFault() {
    //if heap data != NULL, delete heap data
    if (encryptedWords) {
        delete [] encryptedWords;
        encryptedWords = NULL; //Set to NULL after deletion
    }
}

//--------------------------------------------------------------------
//    Public Member Functions
//--------------------------------------------------------------------
void FindFault::findCorruptedLocations(bool * locationArray) {
    faultQueries++;
    try {
        if (locationArray) {
            for (int i = 0; i < this->numOfWords; i++) {
                locationArray[i] =
                (this->encryptedWords[i].getShift() != this->shift);
            }
        }
    } catch (const std::exception& e) {
        std::cout << "\nOh no your bool array was not large enough!\n";
        return;
    }
}

int FindFault::findNumberOfFaults(void) {
    this->faultQueries++; //Increment faultQueries made thus far
    int numDetected = 0; //Number of faults detected
    if (this->encryptedWords) { //If array of encrypted words is not empty
        for (int i = 0; i < this->numOfWords; i++) { //Loop through array
            if (this->encryptedWords[i].getShift() != this->shift) {
                numDetected++;//if shift is not expected shift, increment count
            }
        }
    }
    return numDetected;
}

int FindFault::getNumberOfWords(void) const {
    return this->numOfWords;
}

int FindFault::getStatistics() const {
    return faultQueries;
}

bool FindFault::getHasFaults(void)  {
    faultQueries++; //Increment number of fault queries made
    return (findNumberOfFaults() > 0);
}

int FindFault::getShift(void) const {
    return this->shift;
}

int FindFault::getShiftOfWord(int wordIndex) const {
    if (wordIndex < this->numOfWords && wordIndex >= 0) {
        if (this->encryptedWords) {
            return encryptedWords[wordIndex].getShift();
        }
    }
    return 0;
}

//--------------------------------------------------------------------
//    Operators
//--------------------------------------------------------------------
//Copy assignment operator
FindFault& FindFault::operator= (const FindFault & other) {
    FindFault tmp(other); //Use copy constructor
    *this = std::move(tmp); //This calls the Move Assignment operator
    return *this;
}

//Move assignment operator (I followed an example on the internet to write this)
FindFault& FindFault::operator= (FindFault&& other) {
    if (this->encryptedWords) {//If this object is currently referncing heap mem
        delete [] encryptedWords; //Free up the heap memory
    }
    this->numOfWords = other.numOfWords; //number of words stored on this object
    this->faultQueries = other.faultQueries;
    this->shift = other.shift;
    //(As I understand it) The idea here is to move the ownership of dynamically
    //allocated memory from a temp object to this object.
    this->encryptedWords = other.encryptedWords;
    other.encryptedWords = NULL; //Then revoke the temp objects 'knowledge' of
    //                          the dynamically allocated memory
    return *this;
}

//I feel this operator is justified, but because apparently operators need to go
//completely against the spitir of programming by contract and are not allowed
//to place the object in an invalid state, this operator will not be included
//in the final verison of this class. 
//FindFault& FindFault::operator+=(const std::string& moreWords) {
//    //Use constructor to make a temporary FindFault
//    FindFault tempff(moreWords, this->shift);
//    return (*this += tempff); //Use other overloaded operator
//}

FindFault& FindFault::operator+=(const EncryptWord& ew){
    std::string s; //Used to hold ew's word
    if (ew.getEncryptionState()) { //If ew has encryption turned on
        EncryptWord tempEW(ew); //Construct a copy of ew that's not const
        tempEW.reset(); //Turn off encryption on the temp EncryptWord
        s = tempEW.getWord(); //Set s to the unencrypted word
    }
    else { //if ew's encryption is off, don't need to make a copy of it to turn
    //       encryption off
        s = ew.getWord(); //instead can just get the unencypted word directly
    }
    FindFault temp = FindFault(s); //Don't care how temp is encrypted here
    //                             because the operator used in the return
    //                             statement will make sure the correct
    //                             encryption is used (or a fault may occur)
    //Use the += FindFault operator
    return (*this += temp); //Here is where the same encryption is attempted to
    //                        be set
}


FindFault& FindFault::operator+=(const FindFault& ff){
    //This is the operator that most other operators call for their logic, so
    //it is by far the most complicated
    if (0 == ff.getNumberOfWords()) {
        return *this; //If ff is empty, then no need to do anything
    }
    //Keep track of how many words were originally in this object
    int numWordsThis = this->getNumberOfWords();
    //Figure out how many words there will be after combining the two FindFaults
    this->numOfWords = numWordsThis + ff.getNumberOfWords();
    
    //Next, we need to combine the two arrays
    EncryptWord * thisWrdArray = this->encryptedWords; //Keep track of old array
    //Create a new array the size of the two arrays combined
    this->encryptedWords = new EncryptWord[(unsigned long)this->numOfWords];
    //Copy contents from this into the new array
    for (int i = 0; i < numWordsThis; i++) {
        encryptedWords[i] = thisWrdArray[i];
    }
    //Now for the (slightly more) tricky part
    //Calculate the difference between the shifts of each FindFault
    int shiftDifference = (this->shift - ff.shift);//This is the change in shift
    //Copy contents of the array from ff into the new array
    for (int i = numWordsThis; i < this->numOfWords; i++) {
        encryptedWords[i] = ff.encryptedWords[i - numWordsThis];
        encryptedWords[i].changeShift(encryptedWords[i].getShift()
                                      + shiftDifference);
    }
    //Free up the array the array that's no longer in use
    delete [] thisWrdArray;
    thisWrdArray = NULL; //thisWrdArray will leave scope soon, but just in case
    
    this->faultQueries += ff.faultQueries; //Combine fault queries
    return *this;
}

FindFault FindFault::operator+ (const FindFault& rightFF) const {
    FindFault temp;
    temp += *this;
    temp += rightFF;
    return temp;
}

bool FindFault::operator==(const FindFault& ff) const{
    if (this->numOfWords == ff.numOfWords) { //First see if numberOfWords match
        //Since ff is const and findNumberOfFaults increments statistics, I need
        //to create copies of ff to call its statistics-increasing functions
        FindFault thisCopy = FindFault(*this);
        FindFault ffCopy = FindFault(ff);
        //Next see if the number of faults match
        if (thisCopy.findNumberOfFaults() == ffCopy.findNumberOfFaults()) {
            //if we made it this far, loop through the word array in each
            //FindFault to check to make sure each match up
            for (int i = 0; i < this->numOfWords; i++) {
                if (thisCopy.encryptedWords[i] != ffCopy.encryptedWords[i]) {
                    return false;
                }
            }
            //If we made it through the for loop with each word matching up
            return true; //Then the objects are equal
        }
    }
    //If either numOfWords or numOfFaults failed to match up
    return false; //Then the FindFaults are not equal
}

bool FindFault::operator!=(const FindFault& ff) const {
     return !(*this == ff);
}

std::ostream &operator<<(std::ostream& strm, const FindFault& ff) {
    FindFault ffCopy(ff); //let's me call non-const member functions of ff
    //Make sure array of words exists
    strm << "Number of words encoded by this object: " << ff.numOfWords;
    strm << "\nResult of encoding:\n";
    if ( (ff.encryptedWords)) {
        for (int i = 0; i < ff.numOfWords; i++) {
            strm << ff.encryptedWords[i].getWord() << " ";
        }
    }
    strm << std::endl;
    //strm << "." << std::endl; //Put period at the end?
    
    strm << "Faulty encodings exist: ";
    if (ffCopy.getHasFaults()) {
        strm << " TRUE\n";
    }
    else {
        strm << " FALSE\n";
    }
    strm << "Number of faults detected with encryption: ";
    strm << ffCopy.findNumberOfFaults();
    strm << "\nQueries Made on object regarding finding faults: ";
    strm << ffCopy.faultQueries << std::endl;
    
    if (ffCopy.numOfWords > 0) {
        strm << "\nFindFault Encoding Analysis: \n";
        for (int i = 0; i< ffCopy.numOfWords; i++) {
            strm << "Word Num " << i + INDEX_SHIFT << ": ";
            strm << ffCopy.encryptedWords[i].getWord();
            strm  << "       Encoded with shift: ";
            strm << ffCopy.encryptedWords[i].getShift() << std::endl;
        }
    }
    return strm;
}


//Counts the number of spaces in a string
unsigned long FindFault::countSpaces(const string& inputString) const {
    unsigned long count = 0;
    for (int i = 0; i < (int) inputString.length(); i++) {
        if (inputString.at((unsigned long)i) == SPACE) {
            count++;
        }
    }
    return count;
}

void FindFault::initialize(void) {
    this->numOfWords = 0; //number of words stored on this object
    this->faultQueries = 0;
    this->shift = 0;  //All words should get the same shift, but some may vary
    encryptedWords = NULL; //Array of words
}

void FindFault::parseInputIntoArray(const string& words) {
    //It is assumed that this->shift has already been set elsewhere before this
    //code runs. This code will use whatever value this->shift contains.
    
    string wrds = words + ' '; //Adding a space to end will parse last word
    
    encryptedWords = new EncryptWord[countSpaces(wrds)]; //create array
    numOfWords = 0; //Number of encapsulated words
    unsigned long corruptionChance; //Used to randomly create corruptions
    int corruptedShift; //
    int wordLengthCounter = 0; //Used to make sure words are the correct length
    string currentWord = "";
    
    //Loop through string to seperate out individual words
    for (int i = 0; i <  wrds.length(); i++) {
        corruptionChance = rand() % CORRUPTION_CHANCE_DENOMINATOR;
        //If we find a space, then we have reached the end of a word
        if (wrds.at((unsigned long)i) == SPACE) {
            if (wordLengthCounter >= MIN_WORD_LENGTH) {
                //store word, because it is long enough
                numOfWords++;
                //Now we check to see if word is going to be corrupted or not
                if (corruptionChance == 0) { //If word is going to get corrupted
                    //generate a new value for corruptedShift
                    corruptedShift = shift +
                    (rand() % (CORRUPTION_SHIFT_RANGE_MAX) +
                     CORRUPTION_SHIFT_RANGE_MIN);
                    
                    //Then encrypt word differently from the other words
                    encryptedWords[numOfWords - INDEX_SHIFT] =
                    EncryptWord(currentWord, corruptedShift);
                }
                else { //Else encrypt the word normally using the intended shift
                    encryptedWords[numOfWords - INDEX_SHIFT] =
                    EncryptWord(currentWord, this->shift);
                }
            }
            currentWord = ""; //Reset current word to empty string
            wordLengthCounter = 0;
        }
        else {//If character is not a space, then increment and look at next
            wordLengthCounter++; //Increment word length counter
            currentWord += wrds.at((unsigned long)i);//add character to current
            //                                         word
        }
    }
}
