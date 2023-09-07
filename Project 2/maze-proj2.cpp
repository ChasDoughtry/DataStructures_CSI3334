/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: maze-proj2.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 2
 * Due Date: February 17, 2023
 * This file implements tbe Maze class methods.
 */

#include "maze-proj2.h"

/* Maze Constructor
 * parameters: none
 * This function does nothing.
 */
Maze::Maze(void){
}

/* getStartLocation
 * parameters: none
 * return: Returns the startLocation data member
 *
 * This is a getter function for the startLocation member
 */
Location Maze::getStartLocation(void) const{
    return this->startLocation;
}

/* isValidLocation
 * parameters: loc - location to be checked
 * return: Returns true if loc is a valid location,
 * otherwise returns false.
 *
 * This function uses an iterator to traverse the set.
 * If the iterator reaches the end of the set, then
 * the location was not found.
 */
bool Maze::isValidLocation(const Location &loc) const{
    return validLocations.find(loc) != validLocations.end();
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
    return endLocation == loc;
}

/* >> operator
 *  parameters:
 *      is - input stream where input data is read in from.
 *      m - address of the maze object being changed.
 *  return value: This maze objects data members are
 *      modified with new data from input.
 *
 *  This function reads in an integer n then inserts
 *  n locations into the validLocations set. Then reads
 *  the start and end locations.
 */
istream &operator>>(istream &is, Maze &m){
    m.validLocations.clear();
    int n;
    Location temp;

    is >> n;

    for (int i = 0; i < n; ++i){
        is >> temp;
        m.validLocations.insert(temp);
    }
    is >> m.startLocation >> m.endLocation;

    return is;
}