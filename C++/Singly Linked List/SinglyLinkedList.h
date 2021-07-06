//
// Created by Bi Nguyen on 10/30/20.
//

#ifndef SINGLY_LINKED_LIST_SINGLYLINKEDLIST_H
#define SINGLY_LINKED_LIST_SINGLYLINKEDLIST_H

#include "Node.h"

template <typename T>
class SinglyLinkedList {
    //A LL has attributes head and tails. These are pointers to the Nodes
    //So I want my LL to be able to instantiate a Node object
    //So something like SinglyLinkedList LL {Node {5}} or
    //In order to do the above i need to make a copy constructor for Node
    //However, if we were just to do SinglyLinkedList <int> ll {1}
    //Don't make a mistake and do Node<T*> .... took years to find debug.
    //I also want to do this with my Node<T> a {3}; LL SinglyLinkedList <int> ll{a}
    // but i cant due to ambiguity with the move constructor


private:
    Node<T>* head;
    Node<T>* tail;

public:
    //Constructors
    SinglyLinkedList();
    SinglyLinkedList(T data);
    SinglyLinkedList(Node<T> &&rhs);

    //Destructor
    ~SinglyLinkedList();

    //methods
    bool search(T data);
    bool isEmpty();
    void preprend(T data);
    void append(T data);
    void insertAfter(Node<T>& nodeAfter, T data);
    void deleteAfter(const Node<T>& nodeAfter);



    //Getters
    const Node<T> & getHead() const{
        return head;
    }
    const Node<T> & getTail() const{
        return tail;
    }



};

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(): head{nullptr}, tail{nullptr} {};




template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    head = nullptr;
    tail = nullptr;

}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(T value){
    //This is wrong because temp is automatic storage (i think this means is on the stack) and when you end this constructor,
    //the address of temp may or not be there. So it'll have undefined behavior
    //But if we create Node on the heap, we the address of the Node stays until we delete them.
    //So as soon i create the temp variable. It's not on the heap so after the function ends, the pointer points somewhere else possibly
    // and now my head and tails point at some undefined place in memory

//    auto temp=  Node<T>{value};
//    head = &temp;
//    tail = &temp;

    head = new Node<T>{value};
    tail = head;
}

template<typename T>
bool SinglyLinkedList<T>::search(T data) {
    //Here we don't need to create a temp Node on the heap because we won't need it after the function ends
    Node<T>* currentNode = head;
    while(currentNode != nullptr){
        if(currentNode->getData() == data){
            return true;
        }
        currentNode = currentNode->getNext();
    }
    return false;

}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(Node<T> &&rhs): SinglyLinkedList(rhs.getData()) {}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() {
    return head == nullptr;
}

template<typename T>
void SinglyLinkedList<T>::insertAfter(Node<T> &nodeAfter, T data) {
    //Here I would need to make my node on the heap because I want to  keep my value after the function ends
    auto insertNode = new Node<T>{data};
    //I don't need to go throug the entire list to insert because i know I want to insert after a certain node
    //So i just set the new node to nodeAfter's next
    //But i have to make sure my new node's next is my nodeafter's next
    insertNode->setNext(nodeAfter.getNext());
    nodeAfter.setNext(insertNode);




}

template<typename T>
void SinglyLinkedList<T>::preprend(T data) {
    //So there are two ways to prepend
    //1. The LL is empty
    //2. The LL has atleast one node
    //So i want my new node to point at the current head and make head point at my new node;
    Node<T>* temp = new Node<T>{data};
    temp->setNext(head);
    head = temp;


}

template<typename T>
void SinglyLinkedList<T>::append(T data) {
    //There are two ways to append
    //1. If the LL is empty, we want to prepend
    //2. Else, we want to go make tail's next point to the new node
    if(head == nullptr){
        preprend(data);
        tail = head;
    }else{
        Node<T>* temp = new Node<T> {data};
        tail->setNext(temp);
        tail = temp;
    }





}


#endif //SINGLY_LINKED_LIST_SINGLYLINKEDLIST_H
