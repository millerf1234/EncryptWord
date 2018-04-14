// Author: Forrest Miller
// Filename: FindFault.h
// Date: November 5, 2017
// Version: 1.0 October 24, 2017
//          1.1 Novermber 5, 2017 -- Added overloaded operators

#ifndef FindFault_h
#define FindFault_h

#include <vector>
#include <iostream>
#include <sstream>
#include "EncryptWord.h"

using std::string;
using std::vector;

// Class Overview:
//     This class encapsulates multiple EncryptWord objects. For each
//      encapsulated EncryptWord object there is a chance for the encryption to
//      occur incorrectly, thus causing a 'fault' within the overall encryption.
//      The class operates by taking in a string of upper and lower case
//      characters in addition to spaces. A word is a collection of four or more
//      letters delineated by spaces, any smaller grouping of characters between
//      spaces will cause the word to be skipped in the encoding process.
//      Once the string is encoded (with some of the words reciving faulty
//      encoding), functionality is provided to discover which of the words was
//      encoded incorrectly. There are also statistics tracked to let a user
//      know how many queries have been made to this object regarding if and
//      where encoding errors occured.
//      The encoding shifts and the errors will occur in a random but uniform
//      manner, i.e. all words will receive the same encoding except for the
//      faulty ones, which will all be encoded with different encoding, but all
//      the faulty encodings will occur in the same way.
//
// Valid States: This object is guarenteed to be in a valid state if it is
//               constructed from a string containing only upper and lower case
//               letters and white spaces, any other characters will put the
//               word into an invalid state.
//               The only limit on the number of Encrypted Words that can be
//               contained within this class is the largest size that can be
//               stored as an int, until that point this object will be in a
//               valid state.
//
// Dependencies: This class depends on the EncryptWord class to store each
//               encrypted word.
//
// Anticipated Use: This class is anticipated to be used to store words in an
//                  encrypted format. This class provides functionality for
//                  tracking faults, such as seeing which words are encrypting
//                  differently when compared to other words.
//
// Assumptions:
//      -Constructor will be called with no string or with a string containing
//          only upper and lowercase letters forming words, which are
//          delineated by spaces. Any word shorter than 4 letter will be ignored
//          and skipped in the encoding process.
//      -Calling any of this objects accessor methods will not cause the state
//          of the object to change aside from incrementing the tracking of
//          statistics.
//      -Currently there in no limit to the number of encrypted words that can
//          be stored in a single FindFault object.
//      -Faults will be tracked in the order of the words that were passed into
//          the contructor, i.e. a fault position of 0 will mean there was a
//          fault with encoding the first word, a fault position of 1 for the
//          second word, and so on...
//      -Each time a querry is made to the class to find out the positions of
//          the fault, statistics regarding this are tracked and can be
//          retrieved from the object using the public method getStatistics().
//      -To find which words were encrypted incorrectly in a timely manner, use
//          the findCorruptedLocations method and give it a bool array that
//          is allocated and deallocated outside of this class. Make sure the
//          array is at least as big as there are encrypted words in this class,
//          having the array be too small may have it not written to correctly.
//          Use the getNumberOfWords() method to set size is reccomended. 
//
//Functionality:
//      -This class encapsulates one or more EncryptWord objects, and is
//          intended to be used to find faults that occur when trying to give
//          all the words stored within it the same cypher-shift. Not every word
//          is guarenteed to be encrypted correctly, so this class allows for
//          not only detecting the occurance of faulty encodings but also
//          tracking the location of the faulty encodings, discovering the
//          difference between the faulty encoding and the intended encoding,
//          and also tracking the statistics of its own use in tracking the
//          faulty encodings.
//
//Legal input:
//       -Accepts strings that consist on of upper/lower case letters and
//          spaces. Spaces are used to delineate words of four or more
//          characters. Input words of less than 4 characters in length will be
//          ignored in the encoding process.
//       -The findCorruptedLocations function requires the implementer to
//          declare their own boolean array to store the locations of faults in,
//          then the function will write into the specified array. Having an
//          invalid or too small array will cause the function to not write to
//          the array correctly, but should not cause the program to crash or
//          throw any exceptions.
//
//Illegal Input:
//         Any input string that contains characters that aren't letters or
//         spaces will be encoded incorrectly and will cause undefined behavior
//         of the class.
//         Ending an input string with a space may cause undesirable behavior,
//         but shouldn't break overall functionality
//
//Output:
//         Each of the getters will return the object member data they are
//         getting. Calling getStatistics will return the statistics of queries
//         made to find where faults occur.

//Class Invariants:
//       - Random is used in this class to come up with encoding shifts if they
//          were not specified to the constructor. This class does not seed the
//          random, so if different random results are desired when using this
//          class, please make sure to seed random using srand() before calling
//          this classes constructors.
//       - This class is always willing to let you know if there are or are not
//          faults, so if the constructor without arguments is called, all the
//          methods regarding tracking faults should still work.
//      - This class contains 4 of the big 5 functions every C++ class should
//          contain (as of c++11), so go ahead and try to make it leak memory,
//          it should not ever do so because of its robustness.
//

class FindFault {
public:
    //--------------------------------------------------------------------
    //    Constructors
    //--------------------------------------------------------------------
    FindFault();
    //Description: Default constructor, sets up the object in a valid initial
    //             state but without any words.
    //Preconditions: N/A
    //Postconditions: Object will be empty, so any functionality regarding
    //                checking for faults will return negative (because
    //                technically there are not yet any faults).
    
    FindFault(const string&);
    //Description: Creates a FindFault object with encapsulated words coming
    //             from the string of input words.
    //Preconditions: none
    //Postconditions: The words will attempt to be encoded using a randomly
    //                generated integer-shift between 0 and 25. There is a
    //                during the time each word is encoded that the encoding
    //                will not occur correctly. An incorrect encoding will
    //                be random in how it differs from the intended encoding.
    
    FindFault(const string&, int);
    //Description: Initializes object and sets it equal to the string of words
    //              specified, all which will attempt to be encoded with the
    //              specified integer value. Encodings can be negative. 
    //Preconditions: N/A
    //Postconditions: The words in the string will attempt to be encoded using
    //                the specified encoding value. However, this may fail
    //                causing the words to encode differently. The object will
    //                be in a valid state after this method is called.
    
    //copy constructor
    FindFault(const FindFault &);
    //Description: Sets up a FindFault object which contains the same words with
    //             the same encodings as the specified parameter FindFault obj,
    //             complete with the same errors in encoding. This is a deep
    //             copy, so the array of encrypted words will be initialized in
    //             its own unique memory location.
    //Preconditions: The parameter FindFault object must exist in a valid state
    //Postconditions: This object will exist as a deep-copy of the parameter
    //                object. The array of words will be in a different memory
    //                location than the parameter object's array. The query
    //                statistics will be equal to whatever the parameter obj's
    //                statistics are.
    
    //--------------------------------------------------------------------
    //    Destructor
    //--------------------------------------------------------------------
    ~FindFault();
    //Description: Handles heap memory deallocation once this object leaves
    //             scope
    //Preconditions: Object must exist. Shouldn't cause problems if the object
    //                hasn't ever had valid words fed into it.
    //Postconditions: Object and its data will no longer exist, heap memory used
    //                by the object will be freed for use by other processes and
    //                programs.
    
    //--------------------------------------------------------------------
    //    Public Member Functions
    //--------------------------------------------------------------------
    void findCorruptedLocations(bool *);
    //Description: Writes into an array of booleans the location of each word
    //             that failed to encrypt correctly. i.e. if index 0 of the
    //             bool array gets set to true, then there is an error with the
    //             encryption of the first word, index 1 for the second word and
    //             so on...
    //Preconditions: For this function to function properly, the bool array
    //               should be at least as large as there are encrypted words.
    //               The function getNumberOfWords can be used to determine this
    //              size.
    //Postconditions: Statistics will increase
    
    int findNumberOfFaults(void);
    //Description: Finds the number of words that were encrypted incorrectly
    //Preconditions: Object must exist, can be called even if no words are
    //               encrypted yet.
    //Postconditions: Statistics regarding fault queries will be incremented
    
    int getNumberOfWords(void) const;
    //Description: Returns the total number of words stored within this object
    //Preconditions: Object must exist, can be called even if no words are
    //               encrypted yet.
    //Postconditions: None --  this method is const
    
    
    int getStatistics(void) const;
    //Description: Returns the fault querry statistics, i.e. the number of times
    //             the object was asked about its fault statistics.
    //Preconditions: Object must exist
    //Postconditions: None --  this method is const
    
    bool getHasFaults(void);
    //Description: Returns true if any of the words stored in this object were
    //             encoded in a faulty manner. False if none of the words were
    //             encoded faultily
    //Preconditions: None
    //Postconditions: fault queries will be increased
    
    int getShift(void) const;
    //Description: Returns the shift that should have been used to encode each
    //             word.
    //Preconditions: Object must exist in valid state
    //Postconditions: None --  this method is const
    
    int getShiftOfWord(int) const;
    //Description: Gets the shift of a word encapsulated by this object. Words
    //               are indexed from 0, the int parameter will specify which
    //               word to look at. Will return 0 if parameter is out of
    //               bounds. This method can be used to find out an error in
    //               encryption for each word.
    //Preconditions: The int parameter must match up to a word that has been
    //                encrypted by this object to get a valid shift.
    //Postconditions: Query statistics will increase per each time this function
    //                is called
    
    //--------------------------------------------------------------------
    //    Operators
    //--------------------------------------------------------------------
    //copy assignment operator
    FindFault& operator= (const FindFault & ff);
    //Description: Used to prevent memory leaks when assignment is done with
    //             this object.
    //Preconditions: the parameter ff must exist in a valid state
    //Postconditions: This object will exist as a deep-copy of the parameter
    //                object. The array of words will be in a different memory
    //                location than the parameter object's array. The query
    //                statistics will be equal to whatever the parameter obj's
    //                statistics are.
    
    //Move assignment operator
    FindFault& operator= (FindFault&&);
    //Description: This is a c++11 thing, but prevents memory leaks that
    //             can occur when doing stuff with the object. Allows the object
    //             to be assigned from a temp object (an rvalue)
    //Preconditions: the parameter obj must exist in a valid state
    //Postconditions: This object will exist as a deep-copy of the parameter
    //                object. The array of words will be in a different memory
    //                location than the parameter object's array. The query
    //                statistics will be equal to whatever the parameter obj's
    //                statistics are.
    
//    //Manipulation Operators
    //I feel this operator is justified, but because apparently operators
    //need to go completely against the spirit of programming by contract and
    // are not allowed to place the object in an invalid state (even if we
    // document it), this operator will not be included in the final verison of
    //this class.
//FindFault& operator+=(const std::string& moreWords);
////Description: Parses a string of one or more words composed of letters
////             (upper- and lower-case), seperated by white-space, into an
////             array of encryptWords, encrypts each word with a chance of
////             corruption, and then sticks those words at the end of the
////             collection of encryptwords stored within this object. Any
////             words less than 4 letters in length will be ignored and thus
////             not encrypted. The shift used to Encrypt these words will be
////             the same shift used on the rest of the words, not counting
////             words that may encrypt incorrectly.
////Preconditions: The string moreWords must be composed only of letters and
////               white space. Any characters besides these will result in
////               undefined behavior.
////Postconditions: This object's collection of EncryptWords will contain
////                the additional words created from the string appened to
////                the end of the collection. The number of words counter
////                will increase corresponding to how many words were added,
////                and the number of faults could potentially increase.
    
    FindFault& operator+=(const EncryptWord& ew);
    //Description: Note that the EncryptWord added to the end of this collection
    //             will attempt to be re-encrypted with the shift used on the
    //             words in the rest of this FindFault object, but there is a
    //             chance the encryption there could happen incorrectly.
    //Preconditions:
    //Postconditions: ew's shift will attempt to be changed to match the shift
    //               used for the rest of
    
    FindFault& operator+=(const FindFault& ff);
    //Description: Will add any findFaults querries made to ff to the tally for
    //             this object. Will maintain faults in ff, though their
    //             encryption may change.
    //Preconditions: Parameter ff must be in a valid state.
    //Postconditions:
    
    FindFault operator+ (const FindFault& rightFF) const;
    //Description: Adds two FindFaults together to create a new FindFault
    //             object. The shift of the object on the left will be the shift
    //             used to encrypt words in the resulting object. As such, this
    //             opperation is not commtative (i.e. A + B != B + A). The
    //             statistics of the two objects will be combined, resulting
    //             in their sum being assigned to the new object. 
    //Preconditions: Both FindFault objects should exist in a valid state.
    //Postconditions: Neither findFault will change. The returned find fault
    //                will be a combination of the two, with the FindFault on
    //                the left dictating how the resulting FindFault object will
    //                end up.
    
    //Comparison Operators
    bool operator==(const FindFault&) const; //
    //Description: Compares two FindFault objects to see if they are equal.
    //             Equality is defined as having the same shift and having
    //             each EncryptWord stored within the object evaluate as being
    //             equal.
    //Preconditions: Both this object and the other object should be holding one
    //               or more EncryptWords.
    //Postconditions: None, this operator is const
    
    bool operator!=(const FindFault&) const; //
    //Description: Not equal operator, this operator is defined as being the
    //             negation of the equality operator
    //Preconditions: Both this object and the other object should be holding one
    //               or more EncryptWords.
    //Postconditions: None, this operator is const

    
    friend std::ostream &operator<<(std::ostream&, const FindFault&);
    //Description: formats object info for an ostream to use
    //Preconditions: None really...
    //Postconditions: None, FindFault is a const reference here
    
private:
    int numOfWords;
    int faultQueries;
    int shift; //The intended shift that all words should be encrypted with
    EncryptWord * encryptedWords; //Array of words
    unsigned long countSpaces(const string&) const;//Counts the num of spaces in
    //                                               a string
    void initialize(void) ; //Initializes the object
    void parseInputIntoArray(const string& words);//Encrypts a string into obj
};
#endif /* FindFault_h */
