/* CSI 3334
 * Project 1 -- DFS Maze Solver
 * Filename: stack-proj1.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 1
 * Due Date: February 3, 2023
 * This file implements code LocationStack class
 * and LocationStackNode functions.
 */

#include "stack-proj1.h"

/* LocationStack constructor
 *  parameters: none
 *  Initializes top node to NULL
 */
LocationStack::LocationStack(void){
    this->top = NULL;
}

/* LocationStack Destructor
 * parameters: none
 * Deletes the top node
 */
LocationStack::~LocationStack(){
    delete this->top;
}

/* push
 *  parameters:
 *      loc - location to push onto stack
 *
 *  This function assigns new LocationStackNode to
 *  top and previous top as nextNode to push a new node
 *  onto this stack.
 */
void LocationStack::push(const Location &loc){
    LocationStackNode* temp = new LocationStackNode(loc, this->top);
    top = temp;
}

/* pop
 * parameters: none
 *
 * This function pops the top node by assigning the
 * top to its nextNode and deleting the previous top.
 */
void LocationStack::pop(void){
    assert(!isEmpty());

    if(!this->isEmpty()) {
        LocationStackNode *temp = this->top;
        this->top = this->top->getNextNode();
        temp->setNextNode(NULL);
        delete temp;
    }


}

/* getTop
 *  parameters: none
 *  return value: Returns the locationStackNode on
 *      top of this stack.
 *  Returns location data member of the top node
 */
const Location& LocationStack::getTop(void) const{
    return top->getLocation();
}

/* isEmpty
 *  parameters: none
 *
 *  This function is used to determine if
 *  this stack is empty by checking the top node.
 *
 *  return value: Returns true if top node is NULL,
 *  otherwise returns false
 */
bool LocationStack::isEmpty(void) const{
    return this->top == NULL;
}

/* isOn
 *  parameters:
 *      loc - location to be checked
 *  return value: Returns true if loc is on the stack,
 *  otherwise returns false.
 *
 *  Iterates through stack and compares loc to locations
 *  on this stack.
 */
bool LocationStack::isOn(const Location &loc) const{
    bool onStack = false;
    LocationStackNode* temp = top;

    while(onStack == false && temp != NULL){
        if(temp->getLocation() == loc){
            onStack = true;
        }
        temp = temp->getNextNode();
    }
    return onStack;
}

/* << operator
 *  parameters:
 *      os - output stream where data will be printed
 *      s - The stack being output.
 *  return value: Prints the location on stack s from
 *      bottom to top.
 *  Reverses the next pointers of each node then outputs
 *  the node location and reverses nextNodes again to original
 *  order.
 */
ostream& operator<<(ostream &os, const LocationStack &s){
    assert(!s.isEmpty());
    LocationStackNode *currN = s.top, *prevN = NULL, *nextN = s.top;

    while(currN != NULL){
        nextN = nextN->getNextNode();
        currN->setNextNode(prevN);
        prevN = currN;
        currN = nextN;
    }

    currN = nextN = prevN;
    prevN = NULL;


    while(currN != NULL){
        os << currN->getLocation() << endl;
        nextN = nextN->getNextNode();
        currN->setNextNode(prevN);
        prevN = currN;
        currN = nextN;
    }

    return os;
}
/* LocationStackNode Constructor
 *  parameters:
 *      loc - location data
 *      next - next Node
 *  Initializes location with loc and nextNode with next or NULL
 */
LocationStackNode::LocationStackNode(const Location &loc, LocationStackNode *next){
    this->location = loc;
    this->nextNode = next;
}

/* LocationStackNode destructor
 * parameters: none
 * The destructor for the LocationStackNode class
 */
LocationStackNode::~LocationStackNode(){
    delete this->nextNode;
}

/* getLocation
 * parameters: none
 * return: The location data member.
 * This is a getter function for the Location data member
 * of this object.
 */
const Location& LocationStackNode::getLocation() const{
    return this->location;
}

/* getNextNode
 * parameters: none
 * return: Returns the nextNode data member
 * This is a getter function for the nextNode data member.
 */
LocationStackNode* LocationStackNode::getNextNode() const{
    return this->nextNode;
}

/* setNextNode
 * parameters:
 *     next - the LocationStackNode to be stored
 *         as the nextNode data member.
 * This is a setter function for the nextNode data member.
 */
void LocationStackNode::setNextNode(LocationStackNode *next){
    this->nextNode = next;
}