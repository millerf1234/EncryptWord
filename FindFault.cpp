// Author: Forrest Miller
// Filename: FindFault.cpp
// Date: October 17, 2017
// Version: 0.2 (A lot of this implementation will be rewritten before release)
//
// Description: Not needed (covered in .h)
//
// IMPLEMENTATION INVARIANTS:
// Assumptions:
//             It is assumed all strings passed in to constructors will contain
//               only upper/lower case letters and spaces.
//             It is assumed each word will be seperated by a space
//             Right now I am using a vector to store my EncryptWord objects,
//               but for my actual submission I will be using a dynamically -
//               allocated array of EncryptWord objects.
//             It is assumed that words are supposed to all receive the same
//               encryption, but that corruption will occur by a word receiving
//               a different encryption. All errors will occur in the same way.
//             It is assumed that strings passed in will not end with a space,
//               so a space is manually added to the end of each string to
//               ensure that the last word is encoded
//
//



#include "FindFault.h"

#define SPACE ' '
#define MIN_WORD_LENGTH 4
#define LETTERS_IN_ALPHABET 26
#define CORRUPTION_CHANCE_DENOMINATOR 5  //i.e. 5 gives 1/5 chance of corruption
//                                         per word
#define CORRUPTION_SHIFT_RANGE_MAX 25
#define CORRUPTION_SHIFT_RANGE_MIN 1


using std::string;

FindFault::FindFault() {
    //For this constructor, go through and give everything default values
    faultArray = nullptr;
    hasFaults = false;
    numOfWords = 0;
    shift = 0;
    corruptedShift = 0;
    faultQueries = 0;
    //I have plans to make my other constructors simpler and to make this one
    //the main constructor (i might even remove the other ones entirely)
    // Also in class today we were told we need to store our EncryptWord objects
    //in an array we dynamically declare ourselves, so I will stop using a
    //vector like I am now and will switch it over to a dynamically delcared
    //array
}

FindFault::FindFault(string words) {
    faultArray = nullptr; //Set array for fault tracking to nullptr
    hasFaults = false; //This flag will flip once a fault is detected
    
    shift = rand() % LETTERS_IN_ALPHABET; //Set shift to a random value
    corruptedShift = shift + (rand() % (CORRUPTION_SHIFT_RANGE_MAX
                                            - CORRUPTION_SHIFT_RANGE_MIN
                                            + CORRUPTION_SHIFT_RANGE_MIN)
                                  + CORRUPTION_SHIFT_RANGE_MIN);
    
    faultQueries = 0; //Number of queries made by client
    numOfWords = 0; //Number of encapsulated words
    
    words += SPACE; //Makes loop flush last word by guartenteeing a space at end
    
    int corruptionChance; //Used to randomly create corruptions
    int wordLengthCounter = 0; //Used to make sure words are the correct length
    string currentWord = "";
    //Loop through parameter string to seperate out individual words
    for (int i = 0; i < (int) words.length(); i++) {
        corruptionChance = rand() % CORRUPTION_CHANCE_DENOMINATOR;
        //If we find a space, then we have reached the end of a word
        if (words.at(i) == SPACE) {
            if (wordLengthCounter >= MIN_WORD_LENGTH) {
                //store word, because it is long enough
                numOfWords++;
                //Now we check to see if word is going to be corrupted or not
                if (corruptionChance == 0) { //If word is going to get corrupted
                    //Then encrypt word differently from the other words
                    encryptedWords.push_back(EncryptWord(currentWord, shift
                                                         + corruptedShift));
                }
                else { //Else encrypt the word normally
                    encryptedWords.push_back(EncryptWord(currentWord, shift));
                }
            }
            currentWord = ""; //Reset current word to empty string
            wordLengthCounter = 0;
        }
        else {
            wordLengthCounter++; //Increment word length counter
            currentWord += words.at(i);
        }
    }
    //Now it is time to find the faults that were introduced and track them
    if (numOfWords > 0) {
        faultArray = new bool[numOfWords];
        for (int i = 0; i < numOfWords; i++) {
            if (encryptedWords.at(i).getShift() != this->shift) {
                faultArray[i] = true;
                hasFaults = true;
            }
            else {
                faultArray[i] = false;
            }
        }
    }
    //else handle case of no words
    //Turns out there is nothing to do in the case that there are no words
}

//Update this to match the other constructor once other constructor is working
//FindFault::FindFault(string words, int encodingShiftToUse) {
//    faultArray = nullptr;
//
//    faultQueries = 0; //Number of queries made by client
//    numOfWords = 0; //Number of encapsulated words
//    this->shift = encodingShiftToUse; //Set shift to specified value
//    words += SPACE; //Makes loop flush last word
//
//    int wordLengthCounter = 0; //Used to make sure words are the corret length
//    string currentWord = "";
//    //Loop through parameter string to seperate out individual words
//    for (int i = 0; i < words.length(); i++) {
//        if (words.at(i) == SPACE) {
//            if (wordLengthCounter >= MIN_WORD_LENGTH) {
//                //store word, because it is long enough
//                
//                numOfWords++;
//                encryptedWords.push_back(EncryptWord(currentWord, shift));
//            }
//            currentWord = "";
//            wordLengthCounter = 0;
//        }
//        else {
//            wordLengthCounter++; //Increment word length counter
//            currentWord += words.at(i);
//        }
//    }
//
//    if (numOfWords > 0) {
//        faultArray = new bool[numOfWords];
//        for (int i = 0; i < numOfWords; i++) {
//            faultArray[i] = false;
//        }
//    }
//
//    //else handle case of no words
//}


FindFault::~FindFault() {
    if (faultArray != nullptr) {
        delete [] faultArray;
    }
}

int FindFault::findCorruptedEncryption(void) const {
    return ((this->shift + corruptedShift) % LETTERS_IN_ALPHABET);
}

bool* FindFault::findCorruptedLocations(void) {
    faultQueries++;
    return this->faultArray;
}

int FindFault::findNumberOfFaults(void) {
    faultQueries++; //This member function counts as a fault querie
    if (faultArray == nullptr) {
        return 0;
    } //else
    int faultCounter = 0;
    for (int i = 0; i < numOfWords; i++) {
        if (faultArray[i] != 0) {
            faultCounter++;
        }
    }
    return faultCounter;
}

int FindFault::getNumberOfWords(void) const {
    return this->numOfWords;
}

string FindFault::getEncryptedWords(void) const {
    string s = "";
    for (int i = 0; i < getNumberOfWords(); i++) {
        s += encryptedWords.at(i).getWord();
        s += SPACE;
    }
    return s;
}

int FindFault::getStatistics() const {
    return faultQueries;
}

bool FindFault::getHasFaults(void) const {
    //faultQueries++; //oops can't do this here because function is const
    return hasFaults;
}

int FindFault::getShift() const {
    return this->shift;
}

//Counts the number of spaces in a string -- Might not need this function
int FindFault::countSpaces(const string& inputString) const {
    int count = 0;
    for (int i = 0; i < (int) inputString.length(); i++) {
        if (inputString.at(i) == SPACE) {
            count++;
        }
    }
    return count;
}


