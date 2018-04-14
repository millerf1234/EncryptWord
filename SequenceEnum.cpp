// Author: Forrest Miller
// Filename: SequenceEnum.cpp
// Most Recent Version Date: November 18, 2017
// Version:  11/18/2017 Version 1.0
//
#include "SequenceEnum.h"

//
//      Class Overview:
//         This .cpp file contains the implementation for the SequenceEnumclass.
//          This class features one constructors, getter methods
//          for accessing its class member data, and a member function for
//          allowing guesses to be made as to the word.
//
//          The constructors for this class need to have input words be at least
//          3 characters in length, any word shorter than this will cause the
//          objects to be constructed in an invalid state.

//        DATA PROCESSED:
//          This class is designed to work on strings, and as such each
//            constructor for it requires as a minimum a string as input.
//          This object also stores integers for the shift values. Character
//            arithmatic when handling the ciphering/deciphering of the strings
//            are done using uint8_t type variables to perform the arithmatic.
//            C++ treats uint8_t's as characters.
//
//
//         Class invariants -- See Class invariants in .h file
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
//        Input Strings should be 3 or more characters in length
//        
//

//--------------------------------------------------------------------
//  Constants
//--------------------------------------------------------------------
const unsigned long MIN_WORD_LENGTH = 3ul;
const float CHANCE_ONE_CHAR = 0.75f;
const float CHANCE_TWO_CHAR = 0.5f;
const float CHANCE_THREE_CHAR = 0.25f;
const float CHANCE_FOUR_CHAR = 0.12f;
const float CHANCE_FIVE_CHAR = 0.03f; //(1.0f - 0.5f - 0.25f - 0.15f - 0.08f);
const float CHANCE_MORE_THAN_FIVE_CHAR = 0.0f;
const int ONEHUNDRED = 100;
const int SINGLE_CHAR = 1;
const int TWO_CHAR = 2;
const int THREE_CHAR = 3;
const int FOUR_CHAR = 4;
const int FIVE_CHAR = 5;
const uint8_t CAP_Z = 90u; //Character value of uppercase Z
//const uint8_t CAP_A = 65u; //Character value of uppercase A
const uint8_t LC_Z = 122u; //Character value of lowercase z
const uint8_t LC_A = 97u; //Character value of lowercase a

//--------------------------------------------------------------------
//  Constructor
//--------------------------------------------------------------------
SequenceEnum::SequenceEnum(const std::string& inputWord) {
    this->wordLength = inputWord.length();
    assert(this->wordLength >= MIN_WORD_LENGTH);
    this->originalWord = inputWord; //Track the word that was input
    convertToLower(this->originalWord); //Convert the word to lowerCase
    this->word = this->originalWord; //Set
    this->seqEnumIsActive = true;
    computeSeqEnum();
}

//--------------------------------------------------------------------
//  Functions
//--------------------------------------------------------------------
std::ostream &operator<<(std::ostream& ostrm, const SequenceEnum& se) {
    ostrm << se.emitWord();
    return ostrm;
}

std::string SequenceEnum::emitWord(void) const {
    if (this->seqEnumIsActive) {
        return this->word;
    } //if it's deactivated, just return the original word
    return this->originalWord;
}

bool SequenceEnum::getSeqEnumIsActive(void) const {
    return this->seqEnumIsActive;
}

bool SequenceEnum::toggleSeqEnumActivation(void) {
    this->seqEnumIsActive = !this->seqEnumIsActive;
    return this->seqEnumIsActive;
}

bool SequenceEnum::guessWord(const std::string& guess) const {
    std::string s = guess;
    convertToLower(s);
    if (s == this->originalWord) {
        return true;
    }
    else {
        return false;
    }
}

std::string SequenceEnum::setNewSeqEnum(void) {
    this->word = this->originalWord; //Reset word to its original form
    computeSeqEnum(); //Compute a new SequenceEnum for the word
    return this->word; //Return the new value
}

bool SequenceEnum::operator==(const SequenceEnum& se) const {
    if ((this->originalWord == se.originalWord) && (this->word == se.word)) {
        return true;
    }
    return false;
}

bool SequenceEnum::operator!=(const SequenceEnum& se) const {
    return !(*this == se);
}

//--------------------------------------------------------------------
// Protected Functions
//--------------------------------------------------------------------

void SequenceEnum::convertToLower(std::string& strOfLetters) const {
    //std::cout << "\nString read: " << strOfLetters;
    for (unsigned long i = 0ul; i < strOfLetters.length(); i++) {
        if (strOfLetters.at(i) < LC_A) {
            strOfLetters.at(i) += (LC_Z - CAP_Z);
        }
    }
    //std::cout << "\nConverted String: " << strOfLetters; //For Debug
}

//--------------------------------------------------------------------
// Private Functions
//--------------------------------------------------------------------

void SequenceEnum::computeSeqEnum(void) {
    int charsToRepeat = 0;
    //First we should have it so that word and originalWord are lowercase.
    //originlWord should already be all lowercase, so no need to convert again
    
    //Next we need to find out how many characters will be repeated.
    float randChance = (float)(rand() % ONEHUNDRED) / (float) ONEHUNDRED;
    if (randChance > CHANCE_ONE_CHAR) {
        charsToRepeat = SINGLE_CHAR;
    }
    else if (randChance > CHANCE_TWO_CHAR) {
        charsToRepeat = TWO_CHAR;
    }
    else if (randChance > CHANCE_THREE_CHAR) {
        charsToRepeat = THREE_CHAR;
    }
    else if (randChance > CHANCE_FOUR_CHAR) {
        charsToRepeat = FOUR_CHAR;
    }
    else if (randChance > CHANCE_FIVE_CHAR) {
        charsToRepeat = FIVE_CHAR;
    }
    else if (randChance >= CHANCE_MORE_THAN_FIVE_CHAR) {
        //Just repeat as many characters are as in the word
        charsToRepeat = (int) this->wordLength;
    }
    else { //This should never happen (this is a debug statement)
        //std::cout << "Error! Something went wrong with function rand()!";
       //std::cout << "\nRandom chance that made this occur is: " <<randChance;
    }
    addCharacters(charsToRepeat); //Call other private function to add chars
}

//This function takes in an integer and figures out a way to randomly add a
//corresponding number of extra letters to the string 'word' stored in this obj.
//Some of the logic gets a little hairy, but don't worry it has been extensivly
//tested and it does what it is designed to do
void SequenceEnum::addCharacters(int charsToRepeat) {
    bool repeatFromEnd = false;
    unsigned long randomIndexToGrabCharFrom;
    unsigned long randomIndexToPlaceChar;
    //Check to see if we are repeating more characters than are in the word
    if (charsToRepeat >= (int) this->wordLength) {
        charsToRepeat = (int) this->wordLength; //If there are more, then reduce
        // the number of repeated characters to the number in the orignal word
        repeatFromEnd = true;
    }
    if (repeatFromEnd) {
        for (int i = 0; i < charsToRepeat; i++) {
            //Set random to be an index that exists in string
            randomIndexToGrabCharFrom =(unsigned long) rand() % wordLength;
            this->word += this->word.at(randomIndexToGrabCharFrom);
        }
    }
    else { //if not repeatFromEnd
        for (int i = 0; i < charsToRepeat; i++) {
            randomIndexToGrabCharFrom =(unsigned long) rand() % wordLength;
            //If we are looking at the first character in the word
            if (randomIndexToGrabCharFrom == 0) {
                //Repeat that character (i.e. "cat" would become "ccat")
                word = word.substr(0, SINGLE_CHAR) + word.substr(0, SINGLE_CHAR)
                + word.substr(SINGLE_CHAR); //If we were allowed to type actual
                //numbers into our code, this would be a lot more readable.
            }
            //else if we are looking at the last character in the word
            else if (randomIndexToGrabCharFrom == word.length() - SINGLE_CHAR) {
                // 50/50 chance to add before or after
                if ((rand() % SINGLE_CHAR) == 0) {
                    //Add letter at end
                    word += word.at(randomIndexToGrabCharFrom);
                }
                else { //else
                    //Don't want random index to be first or last letter so
                    //we don't go beyond string index bounds. That's what most
                    //of this confusing logic is checking/fixing
                    randomIndexToPlaceChar = ((rand() % (int)word.length())
                                              - TWO_CHAR);
                    if (randomIndexToPlaceChar < TWO_CHAR) {
                        randomIndexToPlaceChar = TWO_CHAR;
                    }
                    
                    word = word.substr(0, randomIndexToPlaceChar) +
                    word.at(randomIndexToGrabCharFrom) +
                    word.substr(randomIndexToPlaceChar);
                }
            }
            //3-character words were giving me indexing troubles, so I will
            //handle them differently as a seperate case here with a simpler
            //algorithm for repeating characters
            else if (originalWord.length() == MIN_WORD_LENGTH) {
                word = word.substr(0,SINGLE_CHAR) + word.at(SINGLE_CHAR) +
                word.substr(SINGLE_CHAR);
            }
            else { //Else we must be looking at a character in the middle and
                // word is longer than 3 letters
                if (rand() % TWO_CHAR) {
                    word += word.at(randomIndexToGrabCharFrom);
                }
                else {
                    if (rand() % SINGLE_CHAR) {
                        word = word.substr(0, randomIndexToGrabCharFrom)
                        + word.at(randomIndexToGrabCharFrom) +
                        word.substr(randomIndexToGrabCharFrom + TWO_CHAR);
                    }
                    else {
                        randomIndexToPlaceChar = (rand() % (int)word.length());
                        if (randomIndexToPlaceChar < (unsigned long)TWO_CHAR) {
                            randomIndexToPlaceChar = (unsigned long)TWO_CHAR;
                        }
                        if (randomIndexToPlaceChar == (int)word.length()) {
                            randomIndexToPlaceChar -= (unsigned long)TWO_CHAR;
                        }
                        word = word.substr(0, randomIndexToPlaceChar) +
                        word.at(randomIndexToGrabCharFrom) +
                        word.substr(randomIndexToPlaceChar);
                    }
                }
            }
        }
    }
}
