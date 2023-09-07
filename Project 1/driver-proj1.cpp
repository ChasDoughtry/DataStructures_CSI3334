/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: driver-proj1.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 1
 * Due Date: February 1, 2023
 * This file implements code that iteratively
 * solves a maze.
 */


#include <iostream>
#include "maze-proj1.h"
#include "stack-proj1.h"

/* main
 *  parameters:
 *      none
 *  return value: 0 (indicating a successful run)
 *
 *  Main function reads in a maze type from user input. A while loop
 *  used to traverse the maze and push locations on to a stack to
 *  store the path from beginning to end. If a solution is found,
 *  each location is printed in order from start point to end point.
 *  Otherwise, "No solution" is printed.
 */
int main() {
    Maze theMaze;
    Location m, neighbor;
    LocationStack locStack;
    bool solutionFound = true;

    cin >> theMaze;

    m = theMaze.getStartLocation();
    m.iterationBegin();
    locStack.push(m);

    while (solutionFound && !theMaze.isEndLocation(locStack.getTop())) {
        m = locStack.getTop();
        locStack.pop();
        if (!m.iterationDone()) {
            neighbor = m.iterationCurrent();
            neighbor.iterationBegin();
            m.iterationAdvance();
            locStack.push(m);
            if (!locStack.isOn(neighbor) && theMaze.isValidLocation(neighbor)) {
                locStack.push(neighbor);
            }
        }
        else if (locStack.isEmpty()) {
            solutionFound = false;
        }
    }

    if (solutionFound) {
        cout << "Solution found" << endl;
        cout << locStack;
    }
    else {
        cout << "No solution" << endl;
    }

    return 0;
}
