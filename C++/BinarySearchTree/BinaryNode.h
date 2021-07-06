//
// Created by Bi Nguyen on 11/13/20.
//

#ifndef BINARYSEARCHTREE_BINARYNODE_H
#define BINARYSEARCHTREE_BINARYNODE_H


class BinaryNode {
    /*The binary search trees is a node based tree data structure that follows the following requirement:
     * 1. At most 2 children
     * 2. Left child < parent
     * 3. Right child >= parent
    */
    int data;
    BinaryNode* leftChild;
    BinaryNode* rightChild;
public:
    //Constructor
    BinaryNode(int data);

    //methods
    BinaryNode* findMin(BinaryNode*& t);
    BinaryNode* findMax(BinaryNode*& t);
    bool contains(int data, BinaryNode*& t);
    void preOrderTraversal(BinaryNode*& t);
    void postOrderTraversal(BinaryNode*& t);
    void inOrderTraversal(BinaryNode*& t);
    void insert(int data, BinaryNode*& t);
    void remove(int data, BinaryNode*& t);



    //Destructor
    ~BinaryNode();

};


#endif //BINARYSEARCHTREE_BINARYNODE_H
