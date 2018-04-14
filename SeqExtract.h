// Author: Forrest Miller
// Filename: SeqExtract.h
// Most Recent Version Date: November 18, 2017
// Version:  11/18/2017 Version 1.0
//
#ifndef SeqExtract_h
#define SeqExtract_h

#include "SequenceEnum.h"
#include <stdio.h>

//
// Class Overview:
//     This class encapsulates a word and performs a character-repeating
//     operation on the word that can be toggled on or off. This operation is
//     known as SeqExtract, which means that a  subsequence of
//     characters of set length is removed within or at the end of
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
// Dependencies: SequenceEnum
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


class SeqExtract : public SequenceEnum {
private:
    void performSeqExtract(const std::string &);
    bool checkForValidSubseq(const std::string &) const;
    std::string substring;
protected:
    bool seqExtractIsActive;
public:
    //SeqExtract(const std::string & s); //This constructor doesn't make sense
    SeqExtract(const std::string & s, const std::string & substr);
    //Description: Constructs the object from the string and substring
    //Preconditions: both string and substring must contain only letters,
    //               also, substring must be an actual substring within the
    //               main string
    //Postconditions: if preconditions are met, object is guarenteed to be
    //                constructed into a valid state.
    
    virtual std::string emitWord(void) const override;
    //Description: Emits the word from this object based off what is active
    //Preconditions: both string and substring must contain only letters,
    //               also, substring must be an actual substring within the
    //               main string
    //Postconditions: None, method is const
    
    friend std::ostream &operator<<(std::ostream& ostrm, const SeqExtract& se);
    // Description: this is an ostream operator, does not impact this class in
    //              any way
    //Preconditions:This object should have been constructed into a valid state.
    //               having not done so probbaly won't break anything, but none
    //               the less is undefined.

    bool toggleSeqEnumActivation(void) override;
    // Description: Toggles the sequenceEnum off or on. This member function
    //              is how the state of the object transitions.
    // Preconditions: SequenceEnum should be off or on
    // Postconditions: SequenceEnum will be in the opposite state as that which
    //                  it was in before this method was called.
    //
    bool toggleSeqExtractActivation(void);
    // Description: Toggles the seqExtract off or on. This member function
    //              is how the state of the object transitions.
    // Preconditions: SeqExtract should be off or on, same with SeqEnum
    // Postconditions: SeqEtract will be in the opposite state as that which
    //                  it was in before this method was called.
    //
    
    //std::string changeSeq(const std::string &);
    //std::string getSeqString(void) const;
    bool getSeqExtractIsActive(void) const;
    // Description: returns the state of the object.
    // Preconditions: None
    // Postconditions: None, this method is const

    
};

#endif /* SeqExtract_h */
