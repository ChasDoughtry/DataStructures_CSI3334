/* CSI 3334
 * Project 3 -- BST Encryption
 * Filename: bst-student-proj3.h
 * Student name: Chas Doughtry
 * Assignment: Project 3
 * Due Date: March 3, 2023
 * This file implements the methods in the
 * BST, BSTNode and EncryptionTree Classes
 */
#ifndef PROJECT_3_BST_STUDENT_PROJ3_H
#define PROJECT_3_BST_STUDENT_PROJ3_H

#include "bst-prof-proj3.h"

/* BSTNode Destructor
 * parameters: none
 * return: none
 *
 * Deletes the nodes children
 */

template <class Base>
BSTNode<Base>::~BSTNode(){
    delete left;
    delete right;
}

/*
 * printPreorder
 * parameters:
 *     os - ostream object to be print to
 *     indent - indention to be printed
 *
 * Prints a tree or subtree in preorder using
 * recursion. Uses this object as the root.
 */
template <class Base>
void BSTNode<Base>::printPreorder(ostream &os, string indent) const{

    //Base Case
    os << indent << this->data << endl;
    if (this->left){
        this->left->printPreorder(os, indent + "  ");
    }
    else{
        os << indent << "  NULL" << endl;
    }

    if (this->right){
        this->right->printPreorder(os, indent + "  ");
    }
    else{
        os << indent << "  NULL" << endl;
    }
}


/* minNode
 * parameters: none
 * return: The leftmost node of a tree/subtree
 *     using this object as the root.
 *
 * Finds the lowest value node in the
 * tree/subtree.
 */
template <class Base>
const BSTNode<Base>* BSTNode<Base>::minNode() const{
    assert(left);
    BSTNode<Base>* temp;

    if(left) {
        temp = this->left;
        while (temp->left) {
            temp = temp->left;
        }
        return temp;
    }

    return this;
}

/* maxNode
 * parameters: none
 * return: The rightmost node of a tree/subtree
 *     using this object as the root.
 *
 * Finds the highest value node in the
 * tree/subtree.
 */
template <class Base>
const BSTNode<Base>* BSTNode<Base>::maxNode() const{
    assert(right);
    BSTNode<Base>* temp;

    if(right) {
        temp = this->right;
        while (temp->right) {
            temp = temp->right;
        }
        return temp;
    }

    return this;
}

/* insert
 * parameters: item - item being inserted into BST
 * return: none
 *
 * Checks that item is not a duplicate, then
 * inserts item in proper location.
 */
template <class Base>
void BST<Base>::insert(const Base &item){

    if(!root){
        root = new BSTNode<Base>(item);
    }
    else{
        BSTNode<Base>* tempParent, *temp = root;
        bool dup = false;

        while(temp != NULL && !dup){
            tempParent = temp;
            if(item < temp->getData()){
                temp = temp->left;
            }
            else if(temp->getData() < item){
                temp = temp->right;
            }
            else{
                dup = true;
            }
        }

        if(!dup) {
            if (item < tempParent->getData()) {
                tempParent->left = new BSTNode<Base>(item);
            }
            else if(tempParent->getData() < item){
                tempParent->right = new BSTNode<Base>(item);
            }
        }
    }
}

/* remove
 * parameters: item - item being removed from BST
 * return: none
 *
 * Finds the item in
 */
template <class Base>
void BST<Base>::remove(const Base &item){

    if(root != NULL) {
        BSTNode<Base> *toRemove = this->root;
        BSTNode<Base> *parent = toRemove;
        bool notFound = false;

        //Search for item in BST
        while ((toRemove->data < item || item < toRemove->data) && !notFound) {
            parent = toRemove;
            //Search right in tree
            if (toRemove->data < item) {
                if (toRemove->right != NULL) {
                    toRemove = toRemove->right;
                } else { notFound = true; }
            }
                //Search left in tree
            else if (item < toRemove->data) {
                if (toRemove->left != NULL) {
                    toRemove = toRemove->left;
                } else { notFound = true; }
            }
        }

        if (!notFound) {
            //toRemove is a leaf node
            if (toRemove->right == NULL && toRemove->left == NULL) {
                //solve if parent == root
                if (parent == toRemove) {
                    root = NULL;
                } else if (parent->left == toRemove) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
            }
                //toRemove has 1 child
            else if (toRemove->right == NULL || toRemove->left == NULL) {
                //solve if parent == root
                BSTNode<Base> *child = NULL;
                if (toRemove->left != NULL) {
                    child = toRemove->left;
                    toRemove->left = NULL;
                } else {
                    child = toRemove->right;
                    toRemove->right = NULL;
                }
                if (parent == toRemove) {
                    root = child;
                } else if (parent->left == toRemove) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
            }
                //toRemove has 2 children
            else {
                BSTNode<Base> *leftMost = toRemove->right;
                BSTNode<Base> *leftMostParent = toRemove;

                if (leftMost->left != NULL) {
                    while (leftMost->left != NULL) {
                        leftMostParent = leftMost;
                        leftMost = leftMost->left;
                    }
                    leftMostParent->left = leftMost->right;
                    leftMost->right = toRemove->right;
                }
                leftMost->left = toRemove->left;

                if (parent == toRemove) {      //Root = toRemove
                    root = leftMost;
                } else if (parent->left == toRemove) {
                    parent->left = leftMost;
                } else {
                    parent->right = leftMost;
                }
                toRemove->left = toRemove->right = NULL;
            }
            delete toRemove;
        }
    }
}

/* encrypt
 * parameters: item - item to encrypt
 * return: String of the encrypted item
 *
 * Uses a loop to traverse the Tree while
 * storing the path in the string r. Which
 * holds the encrypted version of the item.
 */

template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const{

    string r = "r";
    bool itemFound = false;
    BSTNode<Base> const *temp = this->root;

    //While not a leaf node and item not Found
    while(temp != NULL){
        //Search right in tree
        if(temp->getData() < item){
            r += "1";
            temp = temp->getRight();
        }
        //Search left in tree
        else if(item < temp->getData()){
            r += "0";
            temp = temp->getLeft();
        }
        //item found
        else{
            itemFound = true;
            temp = NULL;
        }
    }

    if(!itemFound){
        r = "?";
    }

    return r;
}

/* decrypt
 * parameters: path - path of the encrypted item
 * return: The address of the encrypted item's data if found,
 *         otherwise returns NULL.
 *
 * Uses a loop to traverse the Tree and find the
 * encrypted item. If not found, NULL is returned.
 */
template <class Base>
const Base* EncryptionTree<Base>::decrypt(const string &path) const{
    BSTNode<Base> const *temp = this->root;

    for (int i = 1; i < path.length() && temp != NULL; i++) {
        if (path[i] == '0') {
            temp = temp->getLeft();
        } else {
            temp = temp->getRight();
        }
    }

    if (temp == NULL) {
        return NULL;
    } else { return &temp->getData(); }
}


#endif //PROJECT_3_BST_STUDENT_PROJ3_H
