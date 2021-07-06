//
// Created by Bi Nguyen on 12/7/20.
//
#include "AVL.h"


int main(int argc, char* argv[]){
    auto tree = AVLTree(argv[1]);
    std::cout << tree.JSON();
}
