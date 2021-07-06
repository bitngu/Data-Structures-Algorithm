//
// Created by Bi Nguyen on 12/5/20.
//

#ifndef PROMPT_AVL_H
#define PROMPT_AVL_H

#include <fstream>
#include <iostream>
#include "BST.h"
#include "json.hpp"

class AVLTree {
public:
    AVLTree(const std::string& filename);
    nlohmann::json JSON();

private:
    BST avl;
    void ll_Rotation(std::shared_ptr<BSTNode> &a);
    void lr_Rotation(std::shared_ptr<BSTNode> &a);
    void rl_Rotation(std::shared_ptr<BSTNode> &a);
    void rr_Rotation(std::shared_ptr<BSTNode> &a);
    void doRotations(std::shared_ptr<BSTNode> recentInsertedNode);
    int updateHeight(const std::shared_ptr<BSTNode> &currentNode);
    int updateBF(const std::shared_ptr<BSTNode> &currentNode);
    void update(std::shared_ptr<BSTNode> lastNode);
};


#endif //PROMPT_AVL_H
