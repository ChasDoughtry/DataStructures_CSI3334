/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: maze-proj1.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 1
 * Due Date: February 3, 2023
 * This file implements code Maze class functions.
 */

#include "maze-proj1.h"

/* Maze Constructor
 * parameters: none
 * Initializes validLocationCount with 0.
 */
Maze::Maze(void){
    validLocationCount = 1;
    validLocations = new Location[validLocationCount];
}

/* Location Destructor
 * parameters: none
 * Deletes the array of validLocations and sets counter to 0.
 */
Maze::~Maze(){
    delete [] validLocations;
    validLocationCount = 0;
}

/* getStartLocation
 * parameters: none
 * return: Returns the startLocation data member
 *
 * This is a getter function for the startLocation member
 */
Location Maze::getStartLocation(void) const{
    return startLocation;
}

/* isValidLocation
 * parameters: loc - location to be checked
 * return: Returns true if loc is a valid location,
 * otherwise returns false.
 *
 * This function iterates through the validLocations array
 * and compares each location to loc until found.
 */
bool Maze::isValidLocation(const Location &loc) const{

    for(int i = 0; i < validLocationCount; ++i){
        if (loc == validLocations[i]){
            return true;
        }
    }
    return false;
}

/* isEndLocation
 * parameters: loc - location to be checked
 * return: Returns true if loc is equal to endLocation
 * member, otherwise returns false.
 *
 * This function is used in the driver to check if a
 * location is the endpoint in the maze.
 */
bool Maze::isEndLocation(const Location &loc) const{
    return loc == endLocation;
}

/* >> operator
 *  parameters:
 *      is - input stream where input data is read in from.
 *      m - address of the maze object being changed.
 *  return value: This maze objects data members are
 *      modified with new data from input.
 *
 *  This function reads integer into validLocationCount, then initializes
 *  validLocations array, then for loop used read input into the array.
 *  Then start and end locations are read from input. Input stream is
 *  returned.
 */
istream &operator>>(istream &is, Maze &m){
    delete[] m.validLocations;
    is >> m.validLocationCount;

    m.validLocations = new Location [m.validLocationCount];

    for(int i = 0; i < m.validLocationCount; ++i){
        is >> m.validLocations[i];
    }
    is >> m.startLocation >> m.endLocation;

    return is;
}

