// Author: Forrest Miller
// Filename: SeqExtract.cpp
// Most Recent Version Date: November 18, 2017
// Version:  11/18/2017 Version 1.0
//

#include "SeqExtract.h"


//
//      Class Overview:
//          This .cpp file contains the implementation for the SeqExtract class.
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

//SeqExtract::SeqExtract(const std::string & s) : SequenceEnum(s) {
//    this->seqEnumIsActive = false;
//    this->seqExtractIsActive = false;
//    this->word = this->originalWord;
//    this->substring = "";
//    //performSeqExtract(); //need a substring seq first
//}


SeqExtract::SeqExtract(const std::string & s, const std::string & substr)
: SequenceEnum(s) {
    this->seqEnumIsActive = false;
    this->seqExtractIsActive = true;
    this->word = this->originalWord;
    if (substr.length() > 0) {
        std::string substrLowerCase = substr;
        convertToLower(substrLowerCase);
        this->substring = substrLowerCase;
        if (checkForValidSubseq(substrLowerCase)) {
            performSeqExtract(substrLowerCase);
        }
        else {
            this->seqExtractIsActive = false;
        }
    }
    else { //substr proffered was empty
        this->substring = "";
        this->seqExtractIsActive = false;
    }
}

std::string SeqExtract::emitWord(void) const {
    if (this->getSeqExtractIsActive() || this->getSeqEnumIsActive()) {
        return this->word;
    }
    else {
        return this->originalWord;
    }
}

std::ostream &operator<<(std::ostream& ostrm, const SeqExtract& se) {
    ostrm << se.emitWord();
    return ostrm;
}

//I don't use this method, so no need to have it in release version
//std::string SeqExtract::changeSeq(const std::string & s) {
//    if (s.length() > 0) {
//        std::string newSubStr = s;
//        convertToLower(newSubStr);
//        if (checkForValidSubseq(newSubStr)) {
//            this->substring = newSubStr;
//            this->seqExtractIsActive = true;
//            performSeqExtract(newSubStr);
//        }
//        //else {
//            //Do Nothing
//        //}
//    }
//    return this->word;
//}

//std::string SeqExtract::getSeqString(void) const {
//    return this->substring;
//}

bool SeqExtract::getSeqExtractIsActive(void) const {
    return this->seqExtractIsActive;
}

//This method will behave differently from parent's method because it needs to
//factor in if SeqExtract is active or not
bool SeqExtract::toggleSeqEnumActivation(void) {
    //Check to see if SeqEnum is active
    if (this->getSeqEnumIsActive()) {
        this->seqEnumIsActive = false;
    }
    else { //If sequenceEnum is off
        if (this->getSeqExtractIsActive()) {
            this->seqExtractIsActive = false;
            this->word = this->originalWord;
        }
        this->seqEnumIsActive = true;
        this->setNewSeqEnum();
    }
    return this->getSeqEnumIsActive();
}

bool SeqExtract::toggleSeqExtractActivation(void) {
    //Check to see if seqEnum is active, note that if it is, then seqExtract
    //must be off
    if (this->getSeqEnumIsActive()) {
        this->toggleSeqEnumActivation(); //Turn it off
        //then turn on sequenceEnum
        if (this->checkForValidSubseq(this->substring)) {
            this->seqExtractIsActive = true;
            performSeqExtract(this->substring);
        }
        else { //Or don't if substring is invalid
            return false;
        }
    }
    else if (this->getSeqExtractIsActive()) {
       // this->word = this->originalWord;
        this->seqExtractIsActive = false;
    }
    else {
        this->seqExtractIsActive = true;
        performSeqExtract(this->substring);
    }
    return this->seqExtractIsActive;
}

bool SeqExtract::checkForValidSubseq(const std::string & substrLowCase) const {
    std::size_t foundMatch = this->originalWord.find(substrLowCase);
    if (foundMatch == std::string::npos) {
        return false;
    }
    return true;
}

void SeqExtract::performSeqExtract(const std::string & substr) {
    //find first occurance of substring.
    std::size_t firstMatch = this->originalWord.find(substr);
    //Check to see if this is at the beginning of the string
    if (firstMatch == 0) {
        this->word = this->originalWord.substr(substr.length());
    }
    //If not, keep everything before start of substring, remove substring, and
    //then keep everything past the end of the substring.
    else {
        this->word = this->originalWord.substr(0, firstMatch) +
        this->originalWord.substr(firstMatch + substr.length());
    }
}
