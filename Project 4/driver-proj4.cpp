/* CSI 3334
 * Project 4 -- AVL Balanced Encryption
 * Filename: driver-proj4.cpp
 * Student name: Chas Doughtry
 * Assignment: Project 4
 * Due Date: March 24, 2023
 * This file implements an algorithm to encrypt and
 * decrypt strings using an AVL balanced tree.
 */

#include "avl-tree-student-proj4.h"
#include <iostream>

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
 *  user wants to print the codebook in preorder traversal. Command "l" indicates the
 *  user wants to print the codebook in level order traversal. Command "q"
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
        else if(input == "p"){                             // Print tree in preorder
            theTree.printPreorder(cout);
        }
        else if(input == "l"){
            theTree.printLevelOrder(cout);
        }
        cin >> input;                                      // Read new command
    }
/*


    AVLTree<string> test1;

    test1.insert("hello");
    test1.insert("world");
    test1.insert("im");
    test1.insert("chas");
    test1.insert("zebra");
    test1.insert("xord");
    test1.insert("zz");
    test1.insert("alexander");
    test1.insert("zain");


    test1.insert("four");
    test1.insert("score");
    test1.insert("and");
    test1.insert("seven");
    test1.insert("years");
    test1.insert("ago");
    //test1.printPreorder();
    test1.printLevelOrder();


    test1.remove("hello");
    test1.remove("alexander");
////
    test1.insert("of");
    test1.insert("go");
    test1.insert("march");
    test1.insert("us");
    test1.insert("green");
    test1.insert("baylor");
    test1.insert("good");
    test1.insert("light");
    test1.insert("gold");
    test1.insert("forever");
    test1.insert("and");
    test1.insert("time");
    test1.insert("to");
    test1.insert("that");
    test1.insert("fling");
    test1.insert("we");
    test1.insert("years");
    test1.insert("as");
    test1.insert("line");
    test1.insert("our");
    test1.insert("guide");
    test1.insert("down");
    test1.insert("shall");
    test1.insert("well");

    test1.insert("the");
    test1.insert("long");
    test1.insert("afar");
    test1.insert("ways");
    test1.insert("onward");
    test1.insert("stars");
    test1.insert("old");

    test1.insert("shine");



    cout << "/////////" << endl;
    test1.printPreorder();
    test1.printLevelOrder();
*/
    return 0;
}
