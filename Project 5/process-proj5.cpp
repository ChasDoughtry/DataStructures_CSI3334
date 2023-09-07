/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System
 * Filename: process-proj5.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 5
 * Due Date: April 14, 2023
 * This file contains the methods for the Process class.
 */
#include "process-proj5.h"


/* Process Constructor
 * Parameters: theId - id number for this object
 * return: none
 *
 * Sets id number and initializes members to
 * default values
 */
Process::Process(int theId){
    id = theId;
    submissionTime =  deadline = requiredTime = 0;
    information = "default";
}

/* run
 * parameters: currentSystemTime - current system time ticks
 * return: new system time
 *
 * Prints information and returns the new time
 */
int Process::run(int currentSystemTime) const{
    cout << "running process id " << this->id << " at " << currentSystemTime << endl;
    cout << information << endl;
    return (currentSystemTime + requiredTime);
}

/* canComplete
 * parameters: currentSystemTime - the current system time
 * return: true if process can be completed, else false
 *
 * If required time is less than or equal to the time left until the
 * deadline, then the process can be completed.
 */
bool Process::canComplete(int currentSystemTime) const{
    return requiredTime <= (deadline - currentSystemTime);
}

/* getId
 * parameters: none
 * return: this object's id number
 *
 * Id getter function
 */
int Process::getId() const{
    return this->id;
}

/* getSubmissionTime
 * parameters: none
 * return: this object's submission time
 *
 * submissionTime getter function
 */
int Process::getSubmissionTime() const{
    return this->submissionTime;
}

/* operator <
 * parameters: p - process being compared
 * return: True if *this is less than p
 *
 * Orders processes first by deadline, then required time,
 * then by id number.
 */
bool Process::operator<(Process const &p) const{

    if(this->deadline == p.deadline){
        if(this->requiredTime == p.requiredTime){
            return this->id < p.id;
        } else{
            return this->requiredTime < p.requiredTime;
        }
    }else{
        return this->deadline < p.deadline;
    }
}

/* operator >>
 * parameters: is - input stream
 *             p -  process object
 * return: input buffer
 *
 * Reads in the values for submission time, then deadline,
 * then required time. Then reads the rest of the line for
 * information.
 */
istream& operator>>(istream &is, Process &p){
    is >> p.submissionTime >> p.deadline >> p.requiredTime;
    getline(is >> ws,p.information); // skips whitespace

    return is;
}