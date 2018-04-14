// Author: Forrest Miller
// Filename: EncryptWord.h
// Most Recent Version Date: November 5, 2017
// Version:  9/28/2017   1.0
//          11/02/2017   1.1   Added overloaded operators, fixed bugs
//
//
#include "EncryptWord.h"
#include <stdint.h>
#include <sstream> //Used to build a string for the guess statistics

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
//        Input Strings should be 4 or more characters in length
//        Avarage Guesses are tracked using a float, so it is assumed that this
//          will provide enough decimal-places of precision to allow the user to
//          get a good feel for the number of guesses they have made
//        Since shifts can be randomly generated, it is assumed the randomly
//          generated shifts will always be a positive integer value between 0
//          and 25. It is also assumed shifts that differ by a multiple of 26
//          are equal (ie that 0=26, -1=25, -2=24, 26=52, etc...)
//

//--------------------------------------------------------------------
//  Constants
//--------------------------------------------------------------------
const int STRING_LENGTH_OF_CHAR = 1; //A character has length of 1
//const int INDEX_SHIFT = 1; //Used for array index notation conversions
const int LETTERS_IN_ALPHABET = 26; //26 letters in standard alphabet
const int MINIMUM_WORD_SIZE = 4; //Smallest word-size for encryption
const int CAP_Z = 90; //Char value for capital Z
const int CAP_A = 65; //Char value for capital A
const uint8_t LC_Z = 122; //Char value for lowercase z
const uint8_t LC_A = 97; //Char value for lowercase a

//--------------------------------------------------------------------
//    Constructors
//--------------------------------------------------------------------
EncryptWord::EncryptWord() {
    word = "";
    shift = 0;
    state = false; //True if shift is on, false if shift is off
    //Set statistics to 0
    numOfGuesses = 0;
    highestGuess = 0;
    lowestGuess = 0;
    sumOfGuesses = 0;
}

EncryptWord::EncryptWord(std::string inputWord) {
    this->shift = rand() % LETTERS_IN_ALPHABET;
    this->numOfGuesses = 0;
    this->highestGuess = 0;
    this->lowestGuess = 0;
    this->sumOfGuesses = 0;
    
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
    this->shift = shift;
    this->numOfGuesses = 0;
    this->highestGuess = 0;
    this->lowestGuess = 0;
    this->sumOfGuesses = 0;
    this->state = true;
    if (!checkLengthRequirement(inputWord)) {
        this->state = false;
        this->word = "";
    }
    else {
        this->word = performCipherShift(inputWord);
    }
}
//Copy Constructor
EncryptWord::EncryptWord(const EncryptWord & otherWord) {
    this->shift = otherWord.shift;
    this->numOfGuesses = otherWord.numOfGuesses;
    this->highestGuess = otherWord.highestGuess;
    this->lowestGuess = otherWord.lowestGuess;
    this->sumOfGuesses = otherWord.sumOfGuesses;
    this->state = otherWord.state;
    this->word = otherWord.word;
}

//--------------------------------------------------------------------
//   Destructor
//--------------------------------------------------------------------
EncryptWord::~EncryptWord(void) {
   //No heap memory to deallocate, but if there were it would happen here
}

//--------------------------------------------------------------------
//    Member Functions
//--------------------------------------------------------------------
bool EncryptWord::getEncryptionState(void) const {
    return this->state;
}

int EncryptWord::getShift(void) const {
    return this->shift;
}

std::string EncryptWord::getWord() const {
    return this->word;
}

void EncryptWord::reset(void) { //turn encryption off/on
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
    //Convert shiftGuess to a value between 0 and 25 representing the same shift
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

void EncryptWord::changeShift(int newShift) {
    //Turn off encryption
    if (this->state) { //Need to turn off old encryption because we are going to
        this->reset(); //overwrite the value used to create the old encryption
    }
    this->shift = newShift;
    this->state = true;
    this->word = performCipherShift(this->word);
    //reset statistics
    this->lowestGuess = 0;
    this->highestGuess = 0;
    this->sumOfGuesses = 0;
    this->numOfGuesses = 0;
}

//--------------------------------------------------------------------
//   Operators
//--------------------------------------------------------------------
EncryptWord& EncryptWord::operator=(const EncryptWord & ew) {//Assignment opratr
    if (&ew == this) { //Check to see if they are the same
        return *this; //If so, then just return the object
    }
    //Reset statistics
    this->sumOfGuesses = ew.sumOfGuesses;
    this->numOfGuesses = ew.numOfGuesses;
    this->highestGuess = ew.highestGuess;
    this->lowestGuess = ew.lowestGuess;
    
    this->state = ew.state;
    this->shift =ew.shift;
    this->word = ew.word;
    return *this;
}

EncryptWord& EncryptWord::operator+=(const std::string& s)  {
    //Gotta not let this operator put word into invalid state
    string letters = ""; //String that will contain only letters
    char c;
    for (unsigned long i = 0; i < s.length(); i++) {
        c = s.at(i);
        if (!((c < CAP_A || c > LC_Z) && (c > CAP_Z && c < LC_A))) {
            letters += c;
        } //there, this sanatizes the string to force object to have to remain
        // in a valid state
    }
    if (this->getEncryptionState()) {
        this->word = this->undoCipherShift(this->word);
    }
    this->word += letters;
    this->word = this->performCipherShift(this->word);
    this->state = true;
    
    //Reset statistics
    this->sumOfGuesses = 0;
    this->numOfGuesses = 0;
    this->highestGuess = 0;
    this->lowestGuess = 0;
    return *this;
}

EncryptWord& EncryptWord::operator+=(const char& c) {
    //So reading the grading rubric, operators are not allowed to put objects
    //into an invalid state, which is stupid because why even practice design
    //by contract. That requirement sounds like defensive programming. Oh well,
    //gotta perform a check to make sure object stays in a valid state.
    if ((c < CAP_A || c > LC_Z) && (c > CAP_Z && c < LC_A)) {
        return *this;
    } //else
    std::string s = "";
    s += c;
    return (*this += s); //Use the other overloaded += operator
}

bool EncryptWord::operator==(const EncryptWord& ew) const { //
    if (this == &ew) { //Check to see if they are the same EncryptWord object
        return true;
    }
    //else -- Time to do some comparisons
    //First check to see if shifts represent the same encryption
    int shiftThis, shiftEw;
    //Set shiftThis
    shiftThis = this->shift;
    //Convert shiftThis to a value between 0 and 25
    if (shiftThis < 0) { //if value is negative
        shiftThis = (shiftThis % LETTERS_IN_ALPHABET) + LETTERS_IN_ALPHABET;
    }
    else {
        shiftThis = shiftThis % LETTERS_IN_ALPHABET;
    }
    //set shiftEw
    shiftEw = ew.shift;
    //Next convert shiftEw to value between 0 and 25
    if (shiftEw < 0) { //if shiftEw is negative
        shiftEw = (shiftEw % LETTERS_IN_ALPHABET) + LETTERS_IN_ALPHABET;
    }
    else {
        shiftEw = shiftEw % LETTERS_IN_ALPHABET;
    }
    //Then compare shiftThis to shiftEw
    if (shiftThis != shiftEw) {
        return false; //If the shifts are different, then objects are not equal
    }
    
    //If the shifts are the same, then compare words
    string wordThis, wordEw;
    wordThis = this->word; //set wordThis
    if (this->state) { //if wordThis is encrypted
        wordThis = undoCipherShift(wordThis); //then unencrypt it
    }
    wordEw = ew.word; //set wordEw
    if (ew.state) { //if wordEw is encrypted
        wordEw = undoCipherShift(wordEw); //then unencrpypt it
    }
    return (wordEw == wordThis);
}

bool EncryptWord::operator!=(const EncryptWord& otherWord) const {
    return !(*this == otherWord);
}


std::ostream& operator<<(std::ostream& strm, const EncryptWord & ew) {
    std::string indent = "   ";
    strm << "Encrypted Word: " << ew.getWord() << std::endl;
    strm << indent << "State: ";
    //Choose string to print out based off objects state
    if (ew.getEncryptionState()) {
        strm << "Encryption On\n";
    }
    else {
        strm << "Encryption Off\n";
    }
    strm << indent << "Shift: " <<  ew.getShift() << std::endl;
    
    //Now need to format Statistics to not exceed 80 chars when printing out
    //and to have additional lines beyond the first line contain indentation
    std::string stats = ""; //create a string for statisitcs
    stats += indent;
    stats += ew.getStatistics();
    unsigned long pos = stats.find("Average"); //Second line of string of stats
    stats.insert(pos, indent);//Inserts indent right before start of second line
    //Now give the newly-formatted stats string to the ostream
    strm << stats;
    //Return the completed ostream
    return strm;
}

//--------------------------------------------------------------------
//    Private Member Functions
//--------------------------------------------------------------------

std::string EncryptWord::getEncryptedWord(void) {
    std::string s;
    if (this->state) { //If the encryption is on currently
        s = this->word; //Then just get the encrypted word
    }
    else { //else if the word is currently not encrypted
        s = this->performCipherShift(this->word); //then encrypt it
    }
    return s; //return the word
}

std::string EncryptWord::getDecodedWord(void) {
    std::string s;
    if (this->state) { //If the encryption is currently on
        s = this->undoCipherShift(this->word); //Then unencrypt the word
    }
    else { //else if the encryption is currently off
        s = this->word; //then just get the unencrypted word
    }
    return s;
}

// Check a string to see if it satisfies length requirement
bool EncryptWord::checkLengthRequirement(std::string const& wordToTest) {
    if (wordToTest.length() < MINIMUM_WORD_SIZE) {
        return false;
    }
    return true;
}

//Encrypts a word using this objects shift
std::string& EncryptWord::performCipherShift(std::string & word) const {
    uint8_t reducedShift = (uint8_t) (this->shift % LETTERS_IN_ALPHABET);
    
    unsigned long lengthOfWord = word.length();
    uint8_t stringIterator;
    for (int i = 0; (unsigned long) i < lengthOfWord; i++) {
        stringIterator = (uint8_t)word.at((unsigned long)i);
        if (stringIterator <= CAP_Z){ //If character is a capital letter
            stringIterator = (stringIterator + reducedShift);
            if (stringIterator > CAP_Z) {
                stringIterator -= LETTERS_IN_ALPHABET;
            }
            else if (stringIterator < CAP_A) {
                stringIterator += LETTERS_IN_ALPHABET;
            }
        }
        else { //if character is a lowercase letter
            stringIterator = (stringIterator + reducedShift);
            if (stringIterator > LC_Z) {
                stringIterator -= LETTERS_IN_ALPHABET;
            }
            else if (stringIterator < LC_A) {
                stringIterator += LETTERS_IN_ALPHABET;
            }
        }
        //Replace String at position i with updated chararcter
        word.replace((unsigned long)i, STRING_LENGTH_OF_CHAR,
                     STRING_LENGTH_OF_CHAR, (char)stringIterator);
    }
    return word;
}

//Undoes the encryption for the word
std::string& EncryptWord::undoCipherShift(std::string & word) const {
    uint8_t reducedShift = (uint8_t) (this->shift % LETTERS_IN_ALPHABET);
    unsigned long lengthOfWord = word.length();
    uint8_t stringIterator;
    for (int i = 0; (unsigned long) i < lengthOfWord; i++) {
        stringIterator = (uint8_t)word.at((unsigned long)i);
        //Check to see if character is capitalized
        if (stringIterator <= CAP_Z){
            stringIterator = (stringIterator - reducedShift);
            if (stringIterator > CAP_Z) {
                stringIterator -= LETTERS_IN_ALPHABET;
            }
            else if (stringIterator < CAP_A) {
                stringIterator += LETTERS_IN_ALPHABET;
            }
        }
        else { //character must then be lowercase
            stringIterator = (stringIterator - reducedShift);
            if (stringIterator > LC_Z) {
                stringIterator -= LETTERS_IN_ALPHABET;
            }
            else if (stringIterator < LC_A) {
                stringIterator += LETTERS_IN_ALPHABET;
            }
        }
        //Replace String at position i with updated chararcter
        word.replace((unsigned long)i, STRING_LENGTH_OF_CHAR,
                     STRING_LENGTH_OF_CHAR, (char)stringIterator);
    }
    return word;
}

//Computes the avarage guess value as a float
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
    }
}
