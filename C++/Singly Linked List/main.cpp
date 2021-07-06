#include <iostream>
#include <vector>
#include "Node.h"
#include "SinglyLinkedList.h"
int main() {

    Node<int> node{1};
    int a = 3;


   SinglyLinkedList<int> ll {Node<int> {2}};
   //How come after this call, the destructor isn't called?
   ll.preprend(4);
   ll.append(7);
   ll.append(3);
   ll.preprend(10);



   ll.search(3);


    SinglyLinkedList<int> ll3 {1};









    return 0;
}