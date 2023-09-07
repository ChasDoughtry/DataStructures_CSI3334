/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: driver-proj2.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 2
 * Due Date: February 17, 2023
 * This file implements code that uses a BFS algorithm
 * to solve the shortest path for a word maze.
 */

#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include "location-proj2.h"
#include "maze-proj2.h"
#include "arrayqueue-student-proj2.h"

/* main
 *  parameters: none
 *  return value: 0 (indicating a successful run)
 *
 *  Main function reads in a maze type from user input. A while loop
 *  used to traverse the maze and add locations on to an ArrayQueue to
 *  store the locations as a BFS. If a solution is found, each word in the
 *  path is printed in order from start point to end point. Otherwise,
 *  "No solution" is printed.
 */

int main(){
/*
    Maze theMaze;
    Location L, neighbor;
    map<Location, Location> prevMap;
    ArrayQueue<Location> q;
    bool isFound = false;
    stack<Location>pathStk;
    */

    Maze theMaze;
    Location L; // neighbor;
    ArrayQueue<Location> q;
    bool isFound = false;
    vector<Location> printOrder;
    map<Location, Location> map;

    cin >> theMaze;

    L = theMaze.getStartLocation();
    q.add(L);


    while (q.getLength() > 0 && !isFound) {
        L = q.getFront();
        q.remove();
        L.iterationBegin();

        while(!L.iterationDone() && !isFound) {
            Location neighbor = L.iterationCurrent();

            if( theMaze.isEndLocation(neighbor)) {
                map[neighbor] = L;
                L = neighbor;
                isFound = true;
            }
            else if (theMaze.isValidLocation(neighbor) && map.find(neighbor) == map.end()) {
                q.add(neighbor);
                map[neighbor] = L;
            }
            L.iterationAdvance();
        }
    }


    if (isFound) {

        cout << "Solution found" << endl;
        for (int i = 0; !(L == theMaze.getStartLocation()); i++) {
            printOrder.push_back(L);
            L = map[L];
        }
        printOrder.push_back(theMaze.getStartLocation());

        for (int i = printOrder.size()-1; i >= 0; i--) {
            cout << printOrder[i] << endl;
        }

/*
        cout << "Solution found:" << endl;

        stack<Location> pathStack;
        Location curr = queueLoc.getFront();

        while(!(curr == maze.getStartLocation())){

            pathStack.push(curr);
            curr = map[curr];
        }

        pathStack.push(curr);

        while(!pathStack.empty()){

            cout << pathStack.top() << endl;
            pathStack.pop();
        }

*/
    }
    else {
        cout << "No solution" << endl;
    }


    return 0;
}
