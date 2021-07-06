#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"

PriorityQueue::PriorityQueue(std::size_t max_size) :
        nodes_(max_size + 1, KeyValuePair()),
        max_size_(max_size),
        size_(0) {
}

void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
    nodes_.at(++size_) = kv;//insert node into next value spot
    heapifyUp(size_);
}

KeyValuePair PriorityQueue::min() {
    return nodes_.at(ROOT);
}

KeyValuePair PriorityQueue::removeMin() {
    KeyValuePair temp = nodes_.at(ROOT); //return value;
    removeNode(ROOT);//remove min
    return temp;
}

bool PriorityQueue::isEmpty() const {
    //heaps always start with position 1, meaning we don't use position 0 but it is still stored. Hence there is always
    //atleast size >=1
    return  size_ == 1;
}

size_t PriorityQueue::size() const {
    //get size of the array
    return  size_;
}

nlohmann::json PriorityQueue::JSON() const {
    nlohmann::json result;
    for (size_t i = 1; i <= size_; i++) {
        nlohmann::json node;
        KeyValuePair kv = nodes_[i];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT) {
            node["parent"] = std::to_string(i / 2);
        }
        if (2 * i <= size_) {
            node["leftChild"] = std::to_string(2 * i);
        }
        if (2 * i + 1 <= size_) {
            node["rightChild"] = std::to_string(2 * i + 1);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
    result["metadata"]["numOperations"] = getNumOps();
    result["metadata"]["maxHeapSize"] = max_size_;
    return result;
}

void PriorityQueue::heapifyUp(size_t i) {
    //i is the child's node position
    size_t  parent = i/2;
    while (getKey(parent) > getKey(i)){//percolate up if parents > child
        nodes_.at(parent).swap(nodes_.at(i));//swap parent and child
        i = parent; //update child
        parent = i/2; //update parent;
    }

}

void PriorityQueue::heapifyDown(size_t i) {
    //i is the parent node position
    size_t leftChild = i*2;
    size_t rightChild = i*2+1;

    //for two child
    while (rightChild <= size_){
        //if parent greater than left child and right child is greater than left child
        if(getKey(i) > getKey(leftChild) && getKey(rightChild) >= getKey(leftChild)){
            nodes_.at(i).swap(nodes_.at(leftChild)); //swap left child with parent
            i = leftChild; //set child as parent

        }else if(getKey(i) > getKey(rightChild) && getKey(leftChild) >= getKey(rightChild)){//if parent > right child nad right < keft
            nodes_.at(i).swap(nodes_.at(rightChild)); //swap right child with parent
            i = rightChild;//set child as parent
        } else {
            break;
        }
        leftChild = i*2; //get next left child
        rightChild = i*2+1;//get next right child
    }

    //for one child
    while(leftChild <= size_){
        if( getKey(i) > getKey(leftChild)) { //when parent larger than left child
            nodes_.at(i).swap(nodes_.at(leftChild));//swap left child with parent
        }
        i = leftChild; //update parent
        leftChild = i * 2;//update new child
    }
}

void PriorityQueue::removeNode(size_t i) {
    nodes_.at(i) = nodes_.at(size_);//replace value with the last value in the heap; not max value
    heapifyDown(i);//reconfigure tree
    //delete the last node
    nodes_.at(size_) = KeyValuePair {0,std::pair<int,int> {0,0}};
    --size_; //decrement size;
}

Key PriorityQueue::getKey(size_t i) {
    return nodes_.at(i).first;//get key of node
}

void PriorityQueue::setNumOps(size_t numOps) {
    PriorityQueue::numOps = numOps;
}

size_t PriorityQueue::getNumOps() const {
    return numOps;
}

Value PriorityQueue::getValue(size_t i) {
    return nodes_.at(i).second;
}



