// Author: Forrest Miller
// Filename: EncryptWord.h
// Date: September 28, 2017
// Version: 1.0
//
//
// Class Overview:
//      This class defines an object that can be used to store words as strings
//      that have been encrypted using a Ceaser cipher-shift. This object stores
//      the shift that was used to encode it, and can have the shift toggled on
//      or off. This object also allows for guessing on what shift is used to
//      encode it's stored word, and provides the functionality of accepting
//      guesses for what the shift used to encode the word is.
//      Words to be encoded should be at least 4 characters in length, words
//      shorter than this will cause the object to be created into an invalid
//      state.
//
// Assumptions:
//      -Constructor will be called with words that are at least 4 characters
//          long. Calling constructor with a shorter-lengthed word will cause
//          the object to be constructed with state set to false and an empty
//          string.
//      -Strings will consist of only letters (either upper or lower case is
//          fine) with no punctuation or spaces. Punctuation may not be encoded
//          correctly within the cipher.
//      -Negative guess values are allowed and are treated as though the shift
//          was being performed in the opposite direction (i.e. a shift of -4 is
//          the same as a shift of +22).
//      -Calling reset with no parameters will deactivate the object and place
//          it into an invalid state. Calling reset with a string parameter will
//          then reactivate the object with that string, making it valid again.
//          Again, please make sure the string is at least four characters.
//      -Calling reset will reset the objects statistics
//      -Calling any of the accessors will not modify the objects state
//      -To change the word stored within the object, use reset.
//
//Functionality:
//      -This class defines an object that stores a word as a string of at least
//         4 characters in length and encrypts the word using a cipher shift.
//         The value of the shift is an integer, and can either be randomly
//         generated or can be specified. The object also allows for guessing
//         as to what the value of the shift is, and will store statistics
//         regarding guess attempts made. Object will only behave properly if
//         word it stores consists entirely of letters with no punctuation,
//         special characters or spaces.
//
//Legal input:
//         Word must be a string of at least four characters and the characters
//         must be either lower case or upper case letters. Shifts can be either
//         negative or positive. This means multiple shifts coudl be correct
//         (ie a shift of -4 is the same as a shift of 22)
//
//Illegal Input:
//         Strings less than 4 characters long will set the objects state to
//         invalid.
//         Including characters in the string that are not letters will cause
//         undefined/unexpected behavior when the shift is performed.
//
//Output:
//         Each of the getters will return the object member data they are
//         getting. Calling getStatistics will return the statistics as a
//         formated string with labels for each statistic.
//         Has member functions for printing out both the encrypted and
//         unencrypted words

#ifndef EncryptWord_h
#define EncryptWord_h

#include <iostream>

using std::string;

class EncryptWord {
public:
    EncryptWord(string);
    // Description: Creates a EncryptWord Object from the parameter string. Will
    //              generate a random shift to encrypt the string with and will
    //              automatically encrypt the string with this shift. Will set
    //              the guess-tracking statistics to their default starting
    //              values. Will set the object into a valid state.
    // Preconditions: string must be at least 4 characters long. Strings less
    //                than this length will place the object into an invalid
    //                state. String should only consist of upper and lower case
    //                letters with no special punctuation or spaces (i.e. A-Z or
    //                a-z).
    // Postconditions: Object will be in a valid state. Guess statistics will be
    //                 set to their default value. Object will contain word
    //                 stored in its encrypted format.
    //                 If Object was created with a word less than 4 characters
    //                 in length, this objects state will start out as false.
    //
    EncryptWord(string, int);
    // Description: Creates a EncryptWord Object from the parameter string. Will
    //              use the specified shift value as the encryption key and will
    //              automatically encrypt the string with this shift. Will set
    //              the guess-tracking statistics to their default starting
    //              values. Will set the object into a valid state.
    // Preconditions: string must be at least 4 characters long. Strings less
    //                than this length will place the object into an invalid
    //                state. String should only consist of upper and lower case
    //                letters with no special punctuation or spaces (i.e. A-Z or
    //                a-z).
    // Postconditions: Object will be in a valid state. Guess statistics will be
    //                 set to their default value. Object will contain word
    //                 stored in its encrypted format.
    //                 If Object was created with a word less than 4 characters
    //                 in length, this objects state will start out as false.

    
    ~EncryptWord(void);
    // Description: Destrutor
    // Preconditions: Object exists
    // Postconditions: Object will no longer exist
    
    bool getState(void) const;
    // Description: Returns 1 if the word is currently encrypted, 0 if the word
    //              is currently not encrypted (ie, the state of the object).
    // Preconditions: The object must exist
    // Postconditions: None, this member function is constant
    
    int getShift(void) const;
    // Description: Returns the current shift used to encode this objects word.
    // Preconditions: The object must exist
    // Postconditions: None, this member function is constant
    
    string getWord(void) const;
    // Description: Returns the word stored within the object
    // Preconditions: The object must be in a valid state
    // Postconditions: None, this member function is constant
    
    void reset(void);
    // Description: Flips the state of the object, turning on/off the cipher
    // Preconditions: Object must be in a valid state
    // Postconditions: Object's cipher-shift will be the opposite of what is was
    //                 before this
    
    string getStatistics(void) const;
    // Description: Returns the current guess statistics stored on the object
    // Preconditions: Object must be in a valid state
    // Postconditions: None, member function is constant
    
    bool verifyShift(int);
    // Description: Used to verify if the integer value parameter is equal to
    //              the shift used to encode the object. Will record guess to
    //              the objects guess statistics. Negative guesses are allowed
    //              and are treated as shifts in the reverse direction.
    // Preconditions: Object must be in the valid state
    // Postconditions: Objects guess statistics will be updated based off the
    //                 guess
    
private:
    //The word to be encapsulated by this class
    string word;
    //Number of characters to shift, should be within interval [0,26)
    int shift;
    bool state; //True if shift is on, false if shift is off
    
    //Statistics about querrys/guesses:
    //Number of guesses
    int numOfGuesses;
    //Highest Guess
    int highestGuess;
    //Lowest Guess
    int lowestGuess;
    //Sum of gueses (for computing avarage)
    int sumOfGuesses;
    //AvarageGuessValue
    //float averageGuessValue;
    
    string getEncryptedWord(void) const;
    // Description: Returns the encrypted word as a string to the user.
    // Preconditions: Object must be in a valid state. Calling this method on an
    //               object in an invalid state will cause bad things to happen.
    // Postconditions: This is constant, so the state of the object will not
    //                 change.
    
    string getDecodedWord(void);
    // Description: Returns the decoded word stored within the object
    // Preconditions: Object must be in valid state.
    // Postconditions: Object will remain in same state as it was when this
    //                 getter was called.
    
    float getAvarageGuess(void) const;
    string& performCipherShift(string&);
    string& undoCipherShift(string&);
    bool checkLengthRequirement(string const&);
    void addValueToGuesses(int);
};

#endif /* EncryptWord_h */



