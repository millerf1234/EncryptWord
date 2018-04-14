// Author: Forrest Miller
// Filename: SequenceEnum.h
// Most Recent Version Date: November 18, 2017
// Version:  11/18/2017 Version 1.0
//
//
#ifndef SequenceEnum_h
#define SequenceEnum_h

#include <stdio.h>
#include <stdlib.h> //rand
#include <iostream>

#define NDEBUG //Uncomment this for release version
#include <assert.h>


//
// Class Overview:
//     This class encapsulates a word and performs a character-repeating
//     operation on the word that can be toggled on or off. This operation is
//     known as SequenceEnum, which means that a random subsequence of
//     characters of random length is randomly repeated within or at the end of
//     the word (the first letter will always remain the same though). This
//     object supports methods for turning on and off the sequence enum, for
//     retriving the modified/unmodified word (depending on if sequenceEnum is
//     on or off), for finding out if the sequnceEnum is on or off, for
//     comparing this SequenceEnums with other SequenceEnums, and generating new
//     sequenceEnums and for guessing what the encapsulated word is.
//
//
//
// Valid States include: Upon construction, if the word proffered to the object
//                       is 3 or more characters, then the object will begin in
//                       a valid state. If the word proffered is shorter than
//                      this, then the object will not be in a valid state, and
//                      in fact does not contain any functionality to return it
//                      to a valid state.
//                       This object should be threadSafe, and will not change
//                      it's data contents if an exception is thrown (or so I
//                      hope).
//                      The object will be constructed into the 'On' state,
//                     which is conviently tracked by a member boolean variable.
//                     While 'on', calling the method emitWord() will cause the
//                      object to emit its altered word. The state can be
//                     toggled off or on using the method toggleState().
//                   Attempting to construct the object with a word containing
//                     non-letter characters will put it in an irreversable
//                     invalid state.
//
//
// Anticipated Use:  This class is intended to be used towards facilitating a
//                      guessing game.
//
// Class Invariants:  -Words must always be three or more characters in length.
//                    -The object contains a boolean member called 'state' that
//                     is true when the SequenceEnum is turned on and false when
//                     the SequenceEnum is turned off. Calling the member
//                     function 'toggle__' will toggle the encryption state.
//                    -Words must be composed entirely of upper and lower case
//                     letters, any characters besides these will result in
//                     undefined behavior.
//
// Assumptions:
//      -Constructor will be called with words that are at least 3 characters
//          long. Calling constructor with a shorter-lengthed word will cause
//          the object to be constructed with state set to false and an empty
//          string.
//      -Strings will consist of only letters (either upper or lower case is
//          fine) with no punctuation or spaces. Punctuation may not be encoded
//          correctly within the seqEnum.
//      -Guess values containing characters that are not letters will never lead
//        to a correct guess.
//
//      -Calling any of the accessors will not modify the objects state
//      -Once set, the word cannot be changed.
//
// Dependencies: None
//
// Functionality:
//      -This class defines an object that stores a word as a string of at least
//         3 characters in length and modifies the word by repeating one or more
//          characters randomly. The class allows the user to guess as to what
//          the encapsulated word might be. There is also functionality to
//          toggle state and to compare two objects of the SequenceEnum type.
//
// Legal input:
//         Word must be a string of at least three characters and the characters
//         must be either lower case or upper case letters. What sequenceEnum
//         does is random for each construction, so constructing the same word
//         into two different objects will most likely result in differing
//         results.
//
//Illegal Input:
//         Strings less than 3 characters long will set the objects state to
//         invalid.
//         Including characters in the string that are not letters will cause
//         undefined/unexpected behavior when the enum is performed.
//
//Output:
//         This object has the method emitWord that emits the word as a string,
//         there is also the friend overloaded ostream operator << that
//          essentially just calls emitWord with the ostream.


class SequenceEnum {
private:
    void computeSeqEnum(void);
    void addCharacters(int);
protected:
    unsigned long wordLength;
    std::string originalWord;
    std::string word;
    bool seqEnumIsActive;
    
    void convertToLower(std::string& strOfLetters) const;
    
public:
    //Construtor
    SequenceEnum(const std::string&);
    //Description: Constructs the object with the string reference proffered as
    //             a parameter. Will turn on the SequenceEnum and perform the
    //             operation on the string. Please construct with only letters
    //             and ensure that the string is at least 3 or more characters.
    //Preconditions: String must contain only letters and must be at least 3
    //               charatcers long.
    //Postconditions: Object will exist in a valid state with SequenceEnum
    //                turned on assuming all the preconditions have been met.
    
    friend std::ostream &operator<<(std::ostream&, const SequenceEnum&);
    // Description: this is an ostream operator, does not impact this class in
    //              any way
    //Preconditions:This object should have been constructed into a valid state.
    //               having not done so probbaly won't break anything, but none
    //               the less is undefined.
    virtual std::string emitWord(void) const;
    //Description: emits the encapsulated word as a string. Depending on the
    //             state of the sequenceEnum, either emits the orignal word or
    //             the modified word.
    // Preconditions: Should have a valid word stored in the object
    // Postconditions: None, this method is const.
    
    bool getSeqEnumIsActive(void) const;
    // Description: returns the state of the object.
    // Preconditions: None
    // Postconditions: None, this method is const
    
    virtual bool toggleSeqEnumActivation(void);
    // Description: Toggles the sequenceEnum off or on. This member function
    //              is how the state of the object transitions.
    // Preconditions: SequenceEnum should be off or on
    // Postconditions: SequenceEnum will be in the opposite state as that which
    //                  it was in before this method was called.
    //
    
    bool guessWord(const std::string&) const;
    //Description: This allows the user to guess what the encapsulated word
    //              might be. This method converts both the encapsulated word
    //              and the user guess to lowercase, so it is caps-insensitive.
    // Preconditions: the guess parameter should contain only letters, else
    //                 this function is pretty much guarenteed to return false.
    //                The guess string should also probably be 3 or more letters
    //                long.
    // Postconditions: none
    
    std::string setNewSeqEnum(void) ;
    // Description: generates a new random sequenceEnum from the encapsulated
    //              word. Does not change the state of the object, so if
    //              SequenceEnum was off when this is called, it will still be
    //              off.
    // Preconditions: Should have a valid word stored in object.
    // Postconditions: A new SequenceEnum will be in place for the word, but the
    //                objects state will be the same as before.
    
    
    bool operator==(const SequenceEnum&) const;
    //Description: Returns true if two sequenceEnums encapsualte the same word
    // Preconditions: Both should be holding valid words
    // Postconditions: N/A
    bool operator!=(const SequenceEnum&) const;
    //Description: Returns false if two sequenceEnums encapsualte the same word
    // Preconditions: Both should be holding valid words
    // Postconditions: N/A
    
    
};


#endif /* SequenceEnum_h */
