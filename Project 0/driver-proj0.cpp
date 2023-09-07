/* CSI 3334
 * Project 0 -- Undo Redo
 * Filename: driver-proj0.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 0
 * Due Date: January 20, 2023
 *This file implements code for typing, undo and redo functions.
 */
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

const int MAX = 10000;
const int MIN = 1;

/* readStack
 *  parameters:
 *      text -- the stack to be printed
 *  return value: void
 *This function empties the text stack into the temp stack in reverse
 * order. Then prints the words to the screen.
 */
void readStack(stack<string>* text);

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 *
 *  Main function takes in the number of commands the user will input. Each line is put on
 *  a string stream. There are 3commands, 't' to type a word, u to undo a typed word and 'r'
 *  to redo an undone word. Then the words are printed using the readStack function from each
 *  stack.
 */
int main(int argc, char **argv) { // QUESTION: WHAT ARE ARGC AND ARGV? GO LOOK THEM UP!
    // these are the two stacks used to store the typed words and the undone
    // words
    stack<string> typing, undo;
    char action;
    string currWord, line;
    int total;
    stringstream ss;

    cin >> total; // Reads # of lines
    assert(total >= MIN && total <= MAX);
    ss.clear();

    //Loop to store user commands into string stream
    for(int i = 0; i <= total; ++i){
        getline(cin, line);
        ss << line << " ";
    }

    for(int i = 0; i < total; ++i){

        //Reads the user command
        ss >> action;
        assert(action == 't' || action != 'u' || action != 'r');
        if (action == 'u') {
            //Undo function

            //if typing stack is empty, error
            if(typing.empty()){
                cout << "nothing to undo on command " << i+1 << endl;
            }

            //else takes top of typing stack and pushes onto undo stack
            //pops top of typing stack
            else{
                undo.push(typing.top());
                typing.pop();
            }

        }
        else if (action == 'r') {

            //if undo stack is empty, error
            if(undo.empty()){
                cout << "nothing to redo on command "<< i+1 << endl;
            }

            //else takes top of undo stack and pushes onto typing stack
            //pops top of undo stack
            else{ //Redo function
                typing.push(undo.top());
                undo.pop();
            }
        }
        else {  //action == 't'
            ss >> currWord;

            //put word on typing stack
            typing.push(currWord);

        }
    }

    //Output
    //Print each stack in reverse
    readStack(&typing);
    cout << endl;
    readStack(&undo);
    cout << endl;

    return 0;
}

void readStack(stack<string>* text){
    stack<string> temp;

    //pushes each element on to temp stack in reverse order
    //pops each element from original stack
    while(!(*text).empty()){
        temp.push((*text).top());
        (*text).pop();
    }

    //prints each element with space in correct order
    //pops each element from temp stack
    while(!temp.empty()){
        cout << temp.top() ;
        temp.pop();
        if(!temp.empty()){
            cout << " ";
        }
    }
}