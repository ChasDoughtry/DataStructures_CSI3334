/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System
 * Filename: driver-proj5.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 5
 * Due Date: April 14, 2023
 * This file implements a OS simulator.
 */

#include <iostream>
#include "process-proj5.h"
#include "arrayheap-student-proj5.h"
using namespace std;

/* main
 *  parameters: none
 *  return value: 0 (indicating a successful run)
 *
 *  Implements an operating system simulator that reads in
 *  processes from the user and determines which processes
 *  can be run. Output details when each process is run or
 *  skipped.
 */
int main() {

    int total, currTime, procCnt, skipCnt = 0, idCnt;
    ArrayHeap<Process> aHeap;
    Process curr, *proc = new Process(0);
    bool atEnd = false;

    currTime = procCnt = skipCnt;

    cin >> total; //read number of processes
    cin >> *proc; // get first process

    while (total > 0){
        while (!atEnd && proc->getSubmissionTime() <= currTime) {
            aHeap.insert(*proc);
            idCnt = proc->getId();
            delete proc;
            proc = new Process(idCnt + 1);

            if ( !(cin >> *proc)) { //stop reading input
                atEnd = true;
            }
        }

        if (aHeap.getNumItems() == 0) {
            currTime++;
        } else {
            curr = aHeap.getMinItem();
            if (curr.canComplete(currTime)) {
                currTime = curr.run(currTime);
                procCnt++;

            } else {
                cout << "skipping process id " << curr.getId() << " at " << currTime << endl;
                skipCnt++;
                currTime++;
            }
            aHeap.removeMinItem();
            total--;
        }
    }
    delete proc;

    cout << "final clock is                 " << currTime;
    cout << "\nnumber of processes run is     " << procCnt;
    cout << "\nnumber of processes skipped is " << skipCnt << endl;

    return 0;
}
