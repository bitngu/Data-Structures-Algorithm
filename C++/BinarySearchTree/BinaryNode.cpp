//
// Created by Bi Nguyen on 11/13/20.
//

#include <iostream>
#include "BinaryNode.h"

BinaryNode::BinaryNode(int data): data{data}, leftChild{nullptr}, rightChild{nullptr} {


}


BinaryNode *BinaryNode::findMin(BinaryNode*& t) {
    if (t->leftChild == nullptr){
        //left most child has the smallest value and it's left child is null
        return t;
    }
    else{
        findMin(t->leftChild);
    }
}

BinaryNode *BinaryNode::findMax(BinaryNode*& t) {
    if(t->rightChild == nullptr){
        //right most child has the largest value and it's right child is null;
        return t;
    }else{
        findMax(t->rightChild);
    }
}

bool BinaryNode::contains(int data, BinaryNode*& t) {
    if(t == nullptr){ //base case; reached the end of the tree
        return false;
    }
    else if (data < t->data){//search left subtree if element is smaller than current data
        contains(data, t->leftChild);
    }
    else if (data > t->data){
        contains(data, t->rightChild);
    }else{
        return true;
    }
}

void BinaryNode::preOrderTraversal(BinaryNode *&t) {
    if (t == nullptr)
        return;
    std::cout << t->data << ",";
    preOrderTraversal(t->leftChild);
    preOrderTraversal(t->rightChild);


}

void BinaryNode::postOrderTraversal(BinaryNode *&t) {
    if (t == nullptr)
        return;
    preOrderTraversal(t->leftChild);
    preOrderTraversal(t->rightChild);
    std::cout << t->data << ",";


}

void BinaryNode::inOrderTraversal(BinaryNode *&t) {
    if (t == nullptr)
        return;
    preOrderTraversal(t->leftChild);
    std::cout << t->data << ",";
    preOrderTraversal(t->rightChild);

}

void BinaryNode::remove(int data, BinaryNode *&t) {
    //look for the item to remove from the tree
    if (data > t->data){
        remove(data, t->rightChild);
    }else if(data < t->data){
        remove(data, t->leftChild);
    }
    //found the item to remove; if the item has 2 children
    else if (t->leftChild != nullptr && t->rightChild != nullptr){
        //look for the next smallest value on the right, and make that this new node
        t->data = findMin(t->rightChild)->data;
        //remove the node that was just "moved" over
        remove(t->data,t->rightChild);
    }
    else{//found the item to remove; if the item has 1 child or less
        BinaryNode* oldNode = t;
        t = (t->leftChild!= nullptr)? t->leftChild : t->rightChild;
        delete t;
    }
}


void BinaryNode::insert(int data, BinaryNode*& t) {

    if (t == nullptr) { //insert new node
        t = new BinaryNode{data};
    }
    //find location to insert new node
    else if(data > t->data){
        insert(data, t->rightChild);
    }else if (data < t->data){
        insert(data, t->leftChild);
    }else {//if the node is already there, do nothing
        return;
    }
}



BinaryNode::~BinaryNode() {
    if(!leftChild){
        delete leftChild;
    }
    if(!rightChild){
        delete rightChild;
    }
}


