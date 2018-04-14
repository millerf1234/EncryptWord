// Author: Forrest Miller
// Filename: EncryptWord.h
// Most Recent Version Date: November 5, 2017
// Version:  9/28/2017   1.0
//          11/02/2017   1.1   Added overloaded operators, fixed bugs

#ifndef EncryptWord_h
#define EncryptWord_h

#include <iostream>  //For std::string

using std::string;

//
// Class Overview:
//     This class stores a string representing a word that can be encrypted and
//     unencrypted using a ceaser-cipher-shift. Words are to be composed
//     entirely of upper and lower case letters, with no other characters
//     allowed. Using any other characters will result in undefined behavior.
//     This class accepts a user-specifed integer to represent a shift, there is
//     no restriction on what value this integer can be. If the user does not
//     specifiy an integer, the class is able to generate a shift randomly.
//     This class contains getter and setter member functions and operators and
//     also contains funtionality to allow a user to use this class to implement
//     a guessing game where the shift used to encrypt a word is guessed at.
//     A word is defined as any string of four or more acceptable characters.
//
//
//
// Valid States include: To be in a valid state, this object must be constructed
//                       to contain a string of at least four characters, with
//                       each character being restricted to the set of upper and
//                       lower case letters. Characters outside of this set will
//                       result in undefined behavior and will constitute the
//                       object entering into an invalid state.
//
//                       Within the valid state, the object's encryption can be
//                       toggled on and off through the use of the member
//                       function reset(). The member function
//                       getEncryptionState() can be used to retrieve the
//                       encrypton state of the object (0 is off, 1 is on).
//
//                       Encryption states are allowed to be any integer large
//                       enough to be stored as an integer within the system
//                       executing this code's arcitecture. Larger shifts can
//                       be expressed as a value within this restriction through
//                       the operation of mod 26. (i.e. use a shift calculated
//                       by shift = (large_int) % 26)
//
// Anticipated Use:  This class can be used to store words with an encryption,
//                   and to encrypt and decrypt them at will. Once a word has
//                   been created in a valid state, every member function has
//                   been set up to allow for them to be called repeatedly
//                   without putting the object into an invalid state. As for
//                   the operators, attempting to add illegal characters to the
//                   word (any characters that aren't letters) will result in
//                   undefined behavior and may cause the object to enter into
//                   an invalid state.
//
// Class Invariants:  -Words must always be four or more characters in length.
//                    -The object contains a boolean member called 'state' that
//                     is true when the encryption is turned on and false when
//                     the encryption is turned off. Calling the member
//                     function 'reset' will toggle the encryption state.
//                    -Words must be composed entirely of upper and lower case
//                     letters, any characters besides these will result in
//                     undefined behavior.
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
//
//      -Calling any of the accessors will not modify the objects state
//      -To change the word stored within the object, use reset.
//
// Dependencies: None
//
// Functionality:
//      -This class defines an object that stores a word as a string of at least
//         4 characters in length and encrypts the word using a cipher shift.
//         The value of the shift is an integer, and can either be randomly
//         generated or can be specified. The object also allows for guessing
//         as to what the value of the shift is, and will store statistics
//         regarding guess attempts made. Object will only behave properly if
//         word it stores consists entirely of letters with no punctuation,
//         special characters or spaces.
//
//
// Legal input:
//         Word must be a string of at least four characters and the characters
//         must be either lower case or upper case letters. Shifts can be either
//         negative or positive. This means multiple shifts could be correct
//         (ie a shift of -4 is the same as a shift of 22)
//
//Illegal Input:
//         Strings less than 4 characters long will set the objects state to
//         invalid.
//         Including characters in the string that are not letters will cause
//         undefined/unexpected behavior when the shift is performed.
//         This rule also applies when using the operator += with both strings
//         and characters.
//
//Output:
//         Each of the getters will return the object member data they are
//         getting. Calling getStatistics will return the statistics as a
//         formated string with labels for each statistic.
//         Has member functions for printing out both the encrypted and
//         unencrypted words
//         The ostring operator<< will return an ostream with all of this
//         objects info formatted into an easy to interpret output, complete
//         with several endl to ensure the ostream flushes (as opposed to '\n'
//         which isn't guarenteed to flush the ostream). Will print the encoded
//         word if state is set to true and the unencoded word if state is false


class EncryptWord {
public:
    //--------------------------------------------------------------------
    //    Constructors
    //--------------------------------------------------------------------
    EncryptWord();
    // Description: Brings an EncryptWord object into existence in a semi-valid
    //              state. Object should be reconstructed further to bring it
    //              into a fully valid state.
    // Preconditions: N/A
    // Postconditions: Object will exist, but its state will not be fully valid.
    //                 The object shall be reconstructed with a different
    //                 constructor than this one before any of its member
    //                 functions will operate correctly. Failing to reconstruct
    //                 will result in undefined behavior.
    
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

    EncryptWord(const EncryptWord & anotherWord); //Copy Constructor
    // Description: Copy Constructor. Creates this object to have the same
    //              member variable values as the parameter object's member
    //              variables.
    // Preconditions: Parameter anotherWord shall be in a valid state
    // Postconditions: This objects member variables will be identical to
    //                 the parameters object's member variables. This includes
    //                 current encryption state and guess statistics.
    
    //--------------------------------------------------------------------
    //    Destructor
    //--------------------------------------------------------------------
    ~EncryptWord(void);
    // Description: Destrutor
    // Preconditions: Object exists
    // Postconditions: Object will no longer exist
    
    //--------------------------------------------------------------------
    //   Public Member Functions
    //--------------------------------------------------------------------
    bool getEncryptionState(void) const;
    // Description: Returns 1 if the word is currently encrypted, 0 if the word
    //              is currently not encrypted (ie, the state of the object).
    // Preconditions: None
    // Postconditions: None, this member function is constant
    
    int getShift(void) const;
    // Description: Returns the current shift used to encode this objects word.
    // Preconditions: None
    // Postconditions: None, this member function is constant
    
    string getWord(void) const;
    // Description: Returns the word stored within the object
    // Preconditions: None
    // Postconditions: None, this member function is constant
    
    void reset(void); 
    // Description: Flips the state of the object, turning on/off the cipher
    // Preconditions: Object should be storing a valid word
    // Postconditions: Object's cipher-shift will be the opposite of what is was
    //                 before this
    
    string getStatistics(void) const;
    // Description: Returns the current guess statistics stored on the object
    // Preconditions: Object should be storing a valid word
    // Postconditions: None, member function is constant
    
    bool verifyShift(int);
    // Description: Used to verify if the integer value parameter is equal to
    //              the shift used to encode the object. Will record guess to
    //              the object's guess statistics. Negative guesses are allowed
    //              and are treated as shifts in the reverse direction. In terms
    //              of group theory, shifts will be equal if they are in the
    //              same group as the one generated by a value between 0 and 25
    //              with respect to addition mod 26 (i.e. if shift is 25 and -1
    //              is guessed, then -1 will be treated as a correct guess.
    //              Other acceptable members of this group would include -27,
    //              -53, -79, ... or 51, 77, 103, 129, ...)
    // Preconditions: Object should contain a valid word
    // Postconditions: Objects guess statistics will be updated based off the
    //                 valued guessed
    
    void changeShift(int);
    //Description: Changes the shift used to encrypt the word to a new specified
    //             value. The new value has no range restrictions and can be
    //             negative. This method will reset statistics
    //Preconditions: Object should be storing a valid word
    //Postconditions: Encryption shift will change to match the specified
    //                parameter. Statistics will be reset. State will be set so
    //                encryption is on regardless of state of object when this
    //                function is called.
    
    //--------------------------------------------------------------------
    //    Operators
    //--------------------------------------------------------------------
    EncryptWord& operator=(const EncryptWord & ew); //Assignment operator
    //Description: Sets this EncryptWord object's member variables to the same
    //             values as another EncryptWord object's member variables
    //Preconditions: The other EncryptWord object should be in a valid state
    //Postconditions:This object's member variables will contain the same values
    //                as the other EncryptWord object's member variables. The
    //                state this object will be the same state as the other
    //                EncryptWord.
    
    EncryptWord& operator+=(const std::string& s);
    //Description: Appends the string onto the end of the encrypted word. Resets
    //             guess statistics. New resulting word will be encrypted.
    //Preconditions: The parameter s should only contain upper and lower case
    //               letters with no special characters or white space.
    //Postconditions: This object's statistics will be reset. The object's word
    //                will now include whatever was in the string at the end of
    //                the word. The Encryption will be turned on no matter what
    //                state the object was in before this operator was used.
    
    EncryptWord& operator+=(const char& c);
    //Description: Appends the character onto the end of the encrypted word.
    //             Resets the guess statistics. Will result in the word being
    //             encrypted regardless of encryption state before operator was
    //             used.
    //Preconditions: The parameter character c shall be a letter of either upper
    //               or lower case, no other character shall be used.
    //Postconditions: This object's statistics will be reset. The object's word
    //                will now include the character at the end of
    //                the word. The Encryption will be turned on no matter what
    //                state the object was in before this operator was used.
    
    bool operator==(const EncryptWord&) const; //
    //Description: Returns false if the encryption for both words don't match or
    //             if the unencrypted word contained in each object don't match.
    //             This is caps sensitive. Note that the encryption for each
    //             object can be represented by multiple shift values. This
    //             operator does not test either objects state or guess
    //             statistics in the comparison process.
    //Preconditions: Both EncryptWords shall be in a valid state.
    //Postconditions: None, this method is const
    
    bool operator!=(const EncryptWord&) const; //
    //Description: Returns true if the encryption for both words don't match or
    //             if the unencrypted word contained in each object don't match.
    //             This is caps sensitive. Note that the encryption for each
    //             object can be represented by multiple shift values. This
    //             operator does not test either objects state or guess
    //             statistics in the comparison process.
    //Preconditions: Both EncryptWords shall be in a valid state.
    //Postconditions: None, this method is const

    friend std::ostream &operator<<(std::ostream&, const EncryptWord&);
    // Description: Returns an ostream with formatted output
    // Preconditions: Object shall be in a valid state
    // Postconditions: This operator has no affect on the EncryptWord object
    
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
    
    string getEncryptedWord(void);
    // Description: Returns the encrypted word as a string to the user.
    // Preconditions: Object must contain a valid word
    // Postconditions: State of object will remain in state it was when this
    //                 method was called.
    
    string getDecodedWord(void);
    // Description: Returns the decoded word stored within the object
    // Preconditions: Object must have a valid word
    // Postconditions: Object will finish in same state as it was when this
    //                 getter was called. 
    
    float getAvarageGuess(void) const;
    string& performCipherShift(string&) const;
    string& undoCipherShift(string&) const;
    bool checkLengthRequirement(string const&);
    void addValueToGuesses(int);
};

#endif /* EncryptWord_h */



