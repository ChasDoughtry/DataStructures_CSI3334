/* CSI 3334
 * Project 3 -- BST Encryption
 * Filename: driver-proj3.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 3
 * Due Date: March 3, 2023
 * This file implements an algorithm to encrypt and
 * decrypt strings.
 */

#include <iostream>
#include <sstream>
#include "bst-student-proj3.h"

using namespace std;

/* main
 *  parameters: none
 *  return value: 0 (indicating a successful run)
 *
 *  The main function uses a while loop to continuously read in commands
 *  from user input. Command "i" followed by a word x indicates the user
 *  wants to insert x into the codebook. Command "r" followed by a word
 *  indicates the user wants to remove x from the codebook. Command "e"
 *  followed by a message indicates the user wants to encrypt the message
 *  using 'r', '0', and '1's. Command "d" followed by an encrypted message
 *  indicates the user wants to decrypt a message. Command "p" indicates the
 *  user wants to print the codebook in preorder traversal. Command "q"
 *  indicates the user wants to quit the program, which ends the while loop.
 */
int main() {

    EncryptionTree<string> theTree;
    string input;
    stringstream ss;

    cin >> input;

    while (input != "q"){
        if(input == "i"){                                  // Insert word
            cin >> input;
            theTree.insert(input);
        }
        else if(input == "r"){                             // Remove word
            cin >> input;
            theTree.remove(input);
        }
        else if(input == "e"){                             // Encrypt line
            getline(cin, input, '\'');
            getline(cin, input, '\'');

            ss.clear();
            ss.str(input);
            ss >> input;
            cout << theTree.encrypt(input);

            while(ss >> input){
                cout << " " << theTree.encrypt(input);
            }
            cout << endl;
        }
        else if(input == "d"){                              // Decrypt word;
            getline(cin, input, '\'');
            getline(cin, input, '\'');

            ss.clear();
            ss.str(input);
            ss >> input;
            if(theTree.decrypt(input) == NULL){
                cout << "?";
            }
            else {
                cout << *(theTree.decrypt(input));
            }

            while(ss >> input){
                if(theTree.decrypt(input) == NULL){
                    cout << " ?";
                }
                else {
                    cout << " " << *(theTree.decrypt(input));
                }
            }
            cout << endl;
        }
        else if(input == "p"){                             // Print tree
            theTree.printPreorder(cout);
        }
        cin >> input;                                      // Read new command
    }

    return 0;
}
