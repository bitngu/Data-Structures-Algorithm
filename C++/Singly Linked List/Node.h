//
// Created by Bi Nguyen on 10/30/20.
//

#ifndef SINGLY_LINKED_LIST_NODE_H
#define SINGLY_LINKED_LIST_NODE_H

template <typename T>
/*A Node */
class Node {
private:
    T data;
    Node<T>* next;

public:
    //Constructors
    Node();
    Node(T value);


    //Getters
    T getData() const {
        return data;
    }

    Node<T>* getNext() const {
        return next;
    }

    void setData(T data);

    void setNext(Node<T> *next);

};

template<typename T>
Node<T>::Node():next{nullptr} {}

template<typename T>
Node<T>::Node(T value): data{value}, next{nullptr} {
}

template<typename T>
void Node<T>::setData(T data) {
    this->data = data;
}

template<typename T>
void Node<T>::setNext(Node<T> *next) {
    this->next = next;
}


#endif //SINGLY_LINKED_LIST_NODE_H
