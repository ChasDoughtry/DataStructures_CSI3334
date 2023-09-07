/* CSI 3334
 * Project 4 -- AVL Balanced Encryption
 * Filename: avl-tree-student-proj4.h
 * Student name: Chas Doughtry
 * Assignment: Project 4
 * Due Date: March 24, 2023
 * This file implements the methods in the
 * AVLTree, AVLNode and EncryptionTree Classes
 */

#ifndef PROJECT_4_AVL_TREE_STUDENT_PROJ4_H
#define PROJECT_4_AVL_TREE_STUDENT_PROJ4_H

#include "avl-tree-prof-proj4.h"
#include <queue>

/* AVLNode Destructor
 * parameters: none
 * return: none
 *
 * Deletes the nodes children
 */
template <class Base>
AVLNode<Base>::~AVLNode(){
    delete left;
    delete right;
}

/* printPreorder
 * parameters:
 *     os - ostream object to be print to
 *     indent - indention to be printed
 *
 * Prints a tree or subtree in preorder using
 * recursion. Uses this object as the root.
 */
template <class Base>
void AVLNode<Base>::printPreorder(ostream &os, string indent) const{
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
const AVLNode<Base>* AVLNode<Base>::minNode() const{
    assert(left);
    AVLNode<Base>* temp;

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
const AVLNode<Base>* AVLNode<Base>::maxNode() const{
    assert(right);
    AVLNode<Base>* temp;

    if(right) {
        temp = this->right;
        while (temp->right) {
            temp = temp->right;
        }
        return temp;
    }

    return this;
}

/* singleRotateLeft
 * parameters: none
 * return: A pointer to the node that takes
 *     this node's position.
 *
 * Performs a single left rotation at this
 * node's position then updates the heights
 * of nodes.
 */
template <class Base>
AVLNode<Base>* AVLNode<Base>::singleRotateLeft(){
    AVLNode<Base> *rightChild = this->right;
    this->right = rightChild->left;
    rightChild->left = this;

    this->updateHeight();
    rightChild->updateHeight();

    return rightChild;
}

/* singleRotateRight
 * parameters: none
 * return: A pointer to the node that takes
 *     this node's position.
 *
 * Performs a single right rotation at this
 * node's position then updates the heights
 * of nodes.
 */
template <class Base>
AVLNode<Base>* AVLNode<Base>::singleRotateRight(){
    AVLNode<Base> *leftChild = this->left;
    this->left = leftChild->right;
    leftChild->right = this;

    this->updateHeight();
    leftChild->updateHeight();

    return leftChild;
}

/* doubleRotateLeftRight
 * parameters: none
 * return: A pointer to the node that takes
 *     this node's position.
 *
 * Performs a double rotation on this node by
 * performing a single left rotation on its left
 * child, then a single right rotation on itself.
 */
template <class Base>
AVLNode<Base>* AVLNode<Base>::doubleRotateLeftRight(){
    this->left = this->left->singleRotateLeft();
    return this->singleRotateRight();
}

/* doubleRotateRightLeft
 * parameters: none
 * return: A pointer to the node that takes
 *     this node's position.
 *
 * Performs a double rotation on this node by
 * performing a single right rotation on its right
 * child, then a single left rotation on itself.
 */
template <class Base>
AVLNode<Base>* AVLNode<Base>::doubleRotateRightLeft(){
    this->right = this->right->singleRotateRight();
    return this->singleRotateLeft();
}

/* insert
 * parameters: item - item being inserted into tree.
 * return: none
 *
 * Checks that item is not a duplicate while storing
 * the path for the rebalancePathToRoot method, then
 * inserts item in proper location. Node heights are
 * updated and the tree is checked for imbalances.
 */
template <class Base>
void AVLTree<Base>::insert(const Base &item){
    vector<AVLNode<Base> *> path; //path from root to insertion

    if(!root){
        root = new AVLNode<Base>(item);
    }
    else{
        AVLNode<Base>* tempParent, *temp = root;
        bool dup = false;

        while(temp != NULL && !dup){
            path.push_back(temp);
            tempParent = temp;

            if(item < temp->getData()){
                temp = temp->left;
            } else if(temp->getData() < item){
                temp = temp->right;
            } else{
                dup = true;
            }
        }

        if(!dup) {
            if (item < tempParent->getData()) {
                tempParent->left = new AVLNode<Base>(item);
            }
            else if(tempParent->getData() < item){
                tempParent->right = new AVLNode<Base>(item);
            }

            for(int i = path.size() - 1; i >= 0; --i){
                path.at(i)->updateHeight();
            }
            this->rebalancePathToRoot(path);

        }
    }
}

/* remove
 * parameters: item - item being removed from Tree.
 * return: none
 *
 * Searches for the item in the tree while storing
 * the path for the rebalancePathToRoot method. If
 * the item is found, it is removed. Then the node
 * heights are updated and the tree is checked for
 * imbalances.
 */
template <class Base>
void AVLTree<Base>::remove(const Base &item){
    vector<AVLNode<Base> *> path; //path from root to affected nodes

    if(root != NULL) {
        AVLNode<Base> *toRemove = this->root;
        AVLNode<Base> *parent = toRemove;
        bool notFound = false;

        //Search for item in BST
        while ((toRemove->data < item || item < toRemove->data) && !notFound) {
            path.push_back(toRemove);
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
                AVLNode<Base> *child = NULL;
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
                AVLNode<Base> *leftMost = toRemove->right;
                AVLNode<Base> *leftMostParent = toRemove;
                int ndx = path.size(); //where toRemove is located in the path

                if (leftMost->left != NULL) {
                    while (leftMost->left != NULL) {
                        path.push_back(leftMost);
                        leftMostParent = leftMost;
                        leftMost = leftMost->left;
                    }
                    leftMostParent->left = leftMost->right;
                    leftMost->right = toRemove->right;
                }
                leftMost->left = toRemove->left;

                path.insert(path.begin() + ndx, leftMost);

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


            for(int i = path.size() - 1; i >= 0; --i){
                path.at(i)->updateHeight();
            }
            this->rebalancePathToRoot(path);

        }
    }

}

/*printLevelOrder
 * parameters:
 *     os - ostream object to be print to
 * return: none
 *
 * Prints a tree in level order iteratively
 * using queue.
 */
template <class Base>
void AVLTree<Base>::printLevelOrder(ostream &os) const{
    const int MAX_ELEMENTS = 20; //maximum number of elements on a line

    if(root == NULL){
        os << "NULL";
    } else {
        queue<AVLNode<Base> *> q;
        int elementCount = 0; //counts number of elements printed on the current line

        q.push(root);

        while (!q.empty()) {
            if(q.front() != nullptr) {
                os << q.front()->data;

                if (q.front()->left != NULL) {
                    q.push(q.front()->left);
                } else {q.push(nullptr);}
                if (q.front()->right != NULL) {
                    q.push(q.front()->right);
                } else{ q.push(nullptr);}

            } else{
                os << "NULL";

            }

            elementCount++; //element added to the line

            if(q.size() > 1){
                //Does this line exceed 20 elements ?
                if(elementCount >= MAX_ELEMENTS){
                    os << endl;
                    elementCount = 0;
                } else{ cout << " ";}

            }
            q.pop();
        }
    }
    os << endl;
}
/* rebalancePathToRoot
 * parameters: path - path to be checked for imbalance
 *                    stored from root to leaf.
 * return: none
 *
 * Uses a loop to traverse each node on the path and
 * checks for any imbalance, then performs rotations
 * if necessary.
 */
template <class Base>
void AVLTree<Base>::rebalancePathToRoot(vector<AVLNode<Base> *> const &path){

    for(int i = path.size() - 1; i >= 0; --i) {
        AVLNode<Base> *curr = path.at(i), *parent;
        int balance = curr->getHeight(curr->left) - curr->getHeight(curr->right);
        //AVLNode<Base>* parent;

        if (i > 0) { //not at the root
            parent = path.at(i - 1);
        }
        if(abs(balance) > 1) { //check for imbalance

            if (balance > 1) { //left tree is taller
                balance = curr->getHeight(path.at(i)->left->left) -
                          curr->getHeight(path.at(i)->left->right);
                if (balance >= 0) {                 //Left-left imbalance
                    if (0 == i) { //at root
                        this->root = curr->singleRotateRight();
                    } else if (parent->left == path.at(i)) {
                        parent->left = curr->singleRotateRight();
                    } else {
                        parent->right = curr->singleRotateRight();
                    }

                } else if (balance < 0) {               //left-right imbalance
                    if (0 == i) { //at root
                        this->root = curr->doubleRotateLeftRight();
                    } else if (parent->left == path.at(i)) {
                        parent->left = curr->doubleRotateLeftRight();
                    } else {
                        parent->right = curr->doubleRotateLeftRight();
                    }
                }
            } else if (balance < -1) { //right tree is taller
                balance = curr->getHeight(path.at(i)->right->left) -
                          curr->getHeight(path.at(i)->right->right);

                if (balance <= 0) {                                   //right-right imbalance
                    if (0 == i) { //root
                        this->root = path.at(i)->singleRotateLeft();
                    } else if (parent->left == path.at(i)) {
                        parent->left = curr->singleRotateLeft();
                    } else {
                        parent->right = curr->singleRotateLeft();
                    }

                } else if (balance > 0) {                            //right-left imbalance
                    if (0 == i) { //root
                        this->root = path.at(i)->doubleRotateRightLeft();
                    } else if (parent->left == path.at(i)) {
                        parent->left = curr->doubleRotateRightLeft();
                    } else {
                        parent->right = curr->doubleRotateRightLeft();
                    }
                }
            }

            //update heights
            for(int j = path.size() - 1; j >= 0; j--){
                path.at(j)->updateHeight();
            }

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
    AVLNode<Base> const *temp = this->root;

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
 * parameters: path - path of the encrypted item.
 * return: The address of the encrypted item's data if found,
 *         otherwise returns NULL.
 *
 * Uses a loop to traverse the Tree and find the
 * encrypted item. If not found, NULL is returned.
 */
template <class Base>
const Base* EncryptionTree<Base>::decrypt(const string &path) const{
    AVLNode<Base> const *temp = this->root;

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

#endif //PROJECT_4_AVL_TREE_STUDENT_PROJ4_H
