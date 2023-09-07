/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: location-proj2.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 2
 * Due Date: February 17, 2023
 * This file implements tbe Location class methods.
 */

#include "location-proj2.h"
#include <cassert>

/* Location Constructor
 * parameters: none
 * Initializes Location data members to
 * default initial values.
 */
Location::Location(){
    //string word = "none";
    iterationMode = CHANGE_LETTER;
    indexToChange = 0;
    nextLetter = 'a';
}

/* Iteration Begin
 *  parameters: none
 *  initializes or resets the Location data members
 */
void Location::iterationBegin(void){
    nextLetter = 'a';
    iterationMode = CHANGE_LETTER;
    indexToChange = 0;
}

/* iterationCurrent
 *  parameters: none
 *
 *  This function computes the next valid Location
 *  one character different than the current word.
 *
 *  return value: Neighbor Location in the current interationMode
 */
Location Location::iterationCurrent(void) const{
    assert(iterationMode != DONE);

    //Create a copy of this object
    Location neighbor;
    neighbor.word = this->word;

    //increment neighbor depending on state
    if(iterationMode == CHANGE_LETTER){
        neighbor.word[indexToChange] = nextLetter;
    }
    else if(iterationMode == INSERT_LETTER){
        neighbor.word.insert(indexToChange, 1, nextLetter);
    }
    else if(iterationMode == DELETE_LETTER){
        neighbor.word.erase(indexToChange,1);
    }

    return neighbor;
}

/* iterationAdvance
 *  parameters: none
 *  Advances the location data members to compute
 *  the correct neighbor for iterationCurrent()
 */
void Location::iterationAdvance(void){
    /*
    if(iterationMode == CHANGE_LETTER){
        if(nextLetter != 'z'){
            nextLetter++;
        }
        else if(indexToChange < word.length()){
            nextLetter = 'a';
            indexToChange++;
        }
        if(nextLetter == word.at(indexToChange)){
            if(nextLetter == 'z'){
                nextLetter = 'a';
            }
            else{
                nextLetter++;
            }
        }
        if (word.length() <= indexToChange && nextLetter == 'z'){
            iterationMode = INSERT_LETTER;
            indexToChange = 0;
            nextLetter = 'a';
        }


    }
    else if(iterationMode == INSERT_LETTER){
        //increment letter if not z
        if(nextLetter != 'z'){
            nextLetter++;
        }
        //if letter cycle has been made increment index;
        else if(indexToChange < word.length()){
            nextLetter = 'a';
            indexToChange++;
        }
        //All insertions have been made
        else{
            iterationMode = DELETE_LETTER;
            indexToChange = 0;
        }
    }
    else if(iterationMode == DELETE_LETTER){
        if(indexToChange < word.length() - 1){
            indexToChange++;
        }
        else{
            iterationMode = DONE;
        }
    }
*/
    if (this->iterationMode == CHANGE_LETTER) {
        if (this->nextLetter < 'z') {
            this->nextLetter++;
        }
        else if (this->word.length() > this->indexToChange) {
            this->nextLetter = 'a';
            this->indexToChange++;
        }

        if (this->word[this->indexToChange] == this->nextLetter) {
            this->nextLetter++;
            if (this->nextLetter > 'z') {
                this->nextLetter = 'a';
                this->indexToChange++;
            }
        }

        if (this->word.length() <= this->indexToChange) {
            this->iterationMode = INSERT_LETTER;
            this->nextLetter = 'a';
            this->indexToChange = 0;
        }
    }
    else if (this->iterationMode == INSERT_LETTER) {
        if (this->nextLetter < 'z') {
            this->nextLetter++;
        }
        else if (this->word.length() > this->indexToChange) {
            this->nextLetter = 'a';
            this->indexToChange++;
        }
        else {
            this->iterationMode = DELETE_LETTER;
            this->indexToChange = 0;
        }
    }
    else if (this->iterationMode == DELETE_LETTER) {
        if (this->indexToChange < this->word.length()-1) {
            this->indexToChange++;
        }
        else {
            this->iterationMode = DONE;
        }
    }

}

/* iterationDone
 *  parameters: none
 *
 *  If the iterationMode is done then the driver can iterate
 *  through the next location's neighbors, this function will
 *  check if a location is done.
 *
 *  return value: returns true if the iteration is done, if else false.
 */
bool Location::iterationDone(void) const{
    return iterationMode == DONE;
}

/* == operator
 *  parameters:
 *      loc - reference to the location being compared to this object.
 *
 *  This function overrides the == operator to compare location objects.
 *
 *  return value: true if this objects word is equal to loc's,
 *  if else false
 */
bool Location::operator==(const Location &loc) const{
    return this->word == loc.word;
}

/* << operator
 *  parameters:
 *      os - output stream where location data will be printed.
 *      loc - reference to the location object being printed.
 *
 *  This function overrides the << operator to output the
 *  word data member of this location object.
 *
 *  return value: Prints the word of this object to os.
 */
ostream &operator<<(ostream &os, const Location &loc){
    os << loc.word;
    return os;
}

/* >> operator
 *  parameters:
 *      is - input stream where input data is read in from.
 *      loc - reference to the location object being changed.
 *
 *  This function overrides the >> operator to read input
 *  and store the data in the word data member of
 *  this location object.
 *
 *  return value: Reads the new wor of this
 *  object from istream.
 */
istream &operator>>(istream &is, Location &loc){
    is >> loc.word;
    return is;
}

/* < operator
 *  parameters:
 *      loc - reference to the location being compared to this object.
 *
 *  This function overrides the < operator to compare location objects.
 *
 *  return value: true if this objects word is less than loc's,
 *  if else false
 */
bool Location::operator<(const Location &loc) const{
    return this->word < loc.word;
}