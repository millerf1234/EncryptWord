// Author: ME
// Filename: FindFault.h
// Date: October 17, 2017
// Version: 0.1 (This version not yet ready for release)
//
//
//
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
//      encoded incorrectly. There are also statistics tracked to let a user know
//      how many queries have been made to this object regarding if and where
//      encoding errors occured.
//      The encoding shifts and the errors will occur in a random but uniform
//      manner, i.e. all words will receive the same encoding except for the
//      faulty ones, which will all be encoded with different encoding, but all
//      the faulty encodings will occur in the same way.
//
// Assumptions:
//      -Constructor will be called with no string or with a string containing
//          only upper and lowercase letters forming words, which are
//          delineated by spaces. Any word shorter than 4 letter will be ignored
//          and skipped in the encoding process.
//      -Calling any of this objects accessor methods will not cause the state
//          of the object to change in any way.
//      -Currently there in no limit to the number of encrypted words that can
//          be stored in a single FindFault object.
//      -Faults will be tracked in the order of the words that were passed into
//          the contructor, i.e. a fault position of 1 will mean there was a
//          fault with encoding the first word, a fault position of 2 for the
//          second word, and so on...
//      -Each time a querry is made to the class to find out the positions of
//          the fault, statistics regarding this are tracked and can be
//          retrieved from the object using the public method getStatistics().
//      -The faulty positions of the misencrypted words are stored in a
//          dynamically sized array of booleans.
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
//          ignored in the encoding process,
//
//Illegal Input:
//         Any input string that contains characters that aren't letters or
//         spaces will be encoded incorrectly and will cause undefined behavior
//         of the class.
//
//Output:
//         Each of the getters will return the object member data they are
//         getting. Calling getStatistics will return the statistics of queries
//         made to find where faults occur.


#ifndef FindFault_h
#define FindFault_h

#include <vector>
#include <iostream>
#include <sstream>
#include "EncryptWord.h"

using std::string;
using std::vector;

class FindFault {
public:
    //Constructors
    
    FindFault();
    //Description: Default constructor, sets up the object in a valid initial
    //             state but without any words.
    //Preconditions: None
    //Postconditions: Object will exist in a valid state
    FindFault(string);
    //Description: Creates a FindFault object with encapsulated words coming
    //             from the string of input words.
    //Preconditions: none
    //Postconditions: Object will exist in a valid state with all the words from
    //                the input string that meet the length requirement being
    //                encoded. Some of the words will recieve a faulty shift.
    //                Statistics will begin to be tracked starting at this point
    //                Also array of fault locations will be created.
    
    //destructor
    ~FindFault();
    //Description: Handles heap memory deallocation once this object leaves
    //             scope
    //Preconditions: Object must exist
    //Postconditions: Object and its data will no longer exist, heap memory used
    //                by the object will be freed for use by other processes and
    //                programs.
    
    int findCorruptedEncryption(void) const;
    //Description: Finds the integer value representing the shift used to
    //               encode the words that were encoded incorrectlys
    //Preconditions: Object must exist in a valid state, calling this method
    //               with an object that has not yet been given words will cause
    //               this method to return 0.
    //Postconditions: None -- this method is const
    
    bool* findCorruptedLocations(void);
    //Description: This returns a pointer to the head of an array of booleans
    //             that represent each word and whether or not that word was
    //             encrypted in a faulty manner
    // Preconditions: Object should contain words
    //Postconditions: Statistics will increase
    
    int findNumberOfFaults(void);
    //Description: Finds the number of words that were encrypted incorrectly
    //Preconditions: Object must exist
    //Postconditions: Statistics regarding fault queries will be incremented
    
    int getNumberOfWords(void) const;
    //Description: Returns the total number of words stored within this object
    //Preconditions: Object must exist
    //Postconditions: None --  this method is const
    
    string getEncryptedWords(void) const;
    //Description: Returns all the words that were encrypted as a string in
    //             their encrypted form. Words that were encrypted in a faulty
    //             manner will be returned with their faulty encryption
    //Preconditions: Object must exist. If no words are contained in the object
    //               this method will return an empty string
    //Postconditions: None --  this method is const

    int getStatistics(void) const;
    //Description: Returns the fault querry statistics, i.e. the number of times
    //             the object was asked about its fault statistics.
    //Preconditions: Object must exist
    //Postconditions: None --  this method is const
    
    bool getHasFaults(void) const;
    //Description: Returns true if any of the words stored in this object were
    //             encoded in a faulty manner. False if none of the words were
    //             encoded faultily
    //Preconditions: Object must exist
    //Postconditions: None --  this method is const
    
    int getShift(void) const;
    //Description: Returns the shift that should have been used to encode each
    //             word.
    //Preconditions: Object must exist
    //Postconditions: None --  this method is const

    //If I have time: //Turns out I don't have time, and I don't plan on having
    //                  driver have direct access to EncryptWord anyways
    //FindFault operator+ (const EncryptWord & ew) const;
    
    //FindFault operator+ (const string & s) const;
    
private:
    int numOfWords;
    int faultQueries;
    int corruptedShift;
    int shift;
    bool* faultArray; //Tracks which words have faults, in order
    bool hasFaults; //True if faults are detected, false otherwise
    
    //EncryptWord* encryptedWordArray = nullptr; //Will implement this later
    vector<EncryptWord> encryptedWords;//Instead implemented as vector (for now)
    
    int countSpaces(const string&) const; //Counts the num of spaces in a string
    
};

#endif /* FindFault_h */
