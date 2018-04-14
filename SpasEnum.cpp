// Author: Forrest Miller
// Filename: SpasEnum.cpp
// Most Recent Version Date: November 18, 2017
// Version:  11/18/2017 Version 1.0
//
#include "SpasEnum.h"

//
//      Class Overview:
//          This .cpp file contains the implementation for the SpasEnum class.
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

const short CHANCE_TO_CONCATENATE = 2;
const short LENGTH_OF_SINGLE_CHARACTER = 1;


SpasEnum::SpasEnum(const std::string & s) : SequenceEnum(s) {
    this->seqEnumIsActive = false;
    this->spasEnumIsActive = true;
    computeSpasEnum(s);
}

void SpasEnum::computeSpasEnum(const std::string & wrd) {
    int substringStart; //Start index for a substring
    int substringLength; //Number of characters in the substring
    short willTruncate = ((short) rand()) % CHANCE_TO_CONCATENATE;
    
    //Need to figure out a random substring, so
    //Step 1) Get the starting index for a substring
    substringStart = rand() % (int) this->wordLength;
    //Step 2) Calculate a length for the substring (not longer than end of word)
    substringLength = rand() %( ((int)this->wordLength) - substringStart);
    //having a length of 0 though won't count, so if 0 make it 1
    if (0 == substringLength) {
        substringLength = LENGTH_OF_SINGLE_CHARACTER;
    }
    //Now that we have a start position and a length, form the substring
    this->substring = wrd.substr(substringStart, substringLength);
    //Finally, Decide to truncate or concatinate
    if (0 == willTruncate) { //Then will concatanate
        this->word = this->originalWord + this->substring;
    }
    else { //else will truncate
        this->word = this->originalWord.substr(0,substringStart) +
                    this->originalWord.substr(substringStart + substringLength);
    }
}

//Don't use therefore don't need this function
//std::string SpasEnum::getSubString(void) const {
  //  return this->substring;
//}

std::string SpasEnum::emitWord() const {
    if (this->getSpasEnumIsActive() || this->getSeqEnumIsActive()) {
        return this->word;
    }
    else { //If it's turned off, return the original word
        return this->originalWord;
    }
}

bool SpasEnum::getSpasEnumIsActive(void) const {
    return this->spasEnumIsActive;
}

bool SpasEnum::toggleSeqEnumActivation(void) {
    //Check to see if SeqEnum is active
    if (this->getSeqEnumIsActive()) {
        this->seqEnumIsActive = false;
    }
    else { //If sequenceEnum is off
        if (this->getSpasEnumIsActive()) {
            this->spasEnumIsActive = false;
            this->word = this->originalWord; //reset the word to originalWord
        }
        this->seqEnumIsActive = true;
        this->setNewSeqEnum();
    }
    return this->getSeqEnumIsActive();
}

bool SpasEnum::toggleSpasEnumActivation(void) {
    if (this->getSeqEnumIsActive()) {
        this->seqEnumIsActive = false;
        this->spasEnumIsActive = true;
        computeSpasEnum(this->originalWord);
    }
    else if (this->spasEnumIsActive) {
        this->spasEnumIsActive = false;
    }
    else {
        this->spasEnumIsActive = true;
        computeSpasEnum(this->originalWord);
    }
    return this->spasEnumIsActive;
}

/*
bool SpasEnum::toggleSeqEnumActivation(void) {
    if (this->getSeqEnumIsActive()) {
        
    }
    else {
        
    }
    return this->getSeqEnumIsActive();
} */
