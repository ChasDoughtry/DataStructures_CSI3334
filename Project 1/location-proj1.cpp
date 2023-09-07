/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: location-proj1.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 1
 * Due Date: February 3, 2023
 * This file implements code Location class functions.
 */

#include "location-proj1.h"
#include <cassert>


/* Location Constructor
 * parameters: none
 * Initializes row and col with 1 and nextDirection to Right.
 */
Location :: Location(){
    row = 1;
    col = 1;
    nextDirection = RIGHT;
}

/* Iteration Begin
 *  parameters: none
 *  initializes or resets the iterator nextDirection to right
 */
void Location::iterationBegin(){
    this->nextDirection = RIGHT;
}

/* iterationCurrent
 *  parameters: none
 *
 *  This function computes the location 1 unit away in
 *  the current direction
 *
 *  return value: Neighbor Location in the current direction
 */
Location Location::iterationCurrent() const{
    assert(nextDirection != DONE);

    //Create a copy of this object
    Location neighbor;
    neighbor.row = this->row;
    neighbor.col = this->col;

    //increment neighbor depending on direction
    if(nextDirection == RIGHT){
        neighbor.col += 1;
    }
    else if(nextDirection == DOWN){
        neighbor.row += 1;
    }
    else if(nextDirection == LEFT){
        neighbor.col -= 1;
    }
    else if(nextDirection == UP){
        neighbor.row -= 1;
    }

    return neighbor;
}

/* iterationAdvance
 *  parameters: none
 *  Increments the direction, which changes the current neighbor
 */
void Location::iterationAdvance(){
    if(nextDirection != DONE){
        nextDirection++;
    }

}

/* iterationDone
 *  parameters: none
 *
 *  If the nextDirection is done then the location can be popped
 *  off the stack in the driver, this function will check if a
 *  location is done.
 *
 *  return value: returns true if the iteration is done, if else false.
 */
bool Location::iterationDone() const{
    return nextDirection == DONE;
}

/* == operator
 *  parameters:
 *      loc - reference to the location being compared to this object.
 *
 *  This function overrides the == operator to compare location objects.
 *
 *  return value: true if this objects row and col are equal to loc's,
 *  if else false
 */
bool Location::operator==(const Location &loc) const {
    return row == loc.row && col == loc.col;
}

/* << operator
 *  parameters:
 *      os - output stream where location data will be printed.
 *      loc - reference to the location object being printed.
 *
 *  This function overrides the << operator to output the
 *  row and col data members of this location object.
 *
 *  return value: Prints the coordinates of this object to os.
 */
ostream &operator<<(ostream &os, const Location &loc){

    os << loc.row << " " << loc.col;

    return os;
}

/* >> operator
 *  parameters:
 *      is - input stream where input data is read in from.
 *      loc - reference to the location object being changed.
 *
 *  This function overrides the >> operator to read input
 *  and store the data in the row and col data members of
 *  this location object.
 *
 *  return value: Reads the new coordinates of this
 *  object from istream.
 */
istream &operator>>(istream &is, Location &loc){
    is >> loc.row >> loc.col;
    return is;
}

//Test Cases

/* #1
4
0 0
1 0
0 1
1 1
0 1
0 0

 */

/* #2
9
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
1 2
0 2

 */

/* #3
12
0 0
0 1
0 2
0 3
1 0
1 3
2 0
2 3
3 0
3 1
3 2
3 3
1 3
0 3
 */

/* #4
17
0 0
0 1
0 2
0 4
1 0
1 2
1 4
2 0
2 2
2 4
3 0
3 4
4 0
4 1
4 2
4 3
4 4
2 2
0 4

 */

/* #5
9
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
1 0
1 1

 */

/* #6
13
0 0
0 1
0 2
0 3
1 0
1 2
2 0
2 1
2 2
2 3
3 0
3 1
3 2
2 2
0 1

 */

/* #7
6
0 0
0 1
1 1
1 2
2 1
2 2
1 2
0 0

*/

/* #8
7
0 0
0 1
0 2
0 3
1 0
2 0
3 0
0 3
3 0
 */

/* #9
5
0 0
1 0
2 0
3 0
4 0
4 0
0 0
 */

/* #10
5
0 0
0 1
0 2
0 3
0 4
0 0
0 4
 */
