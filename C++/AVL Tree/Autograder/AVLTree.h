//
// Created by Bi Nguyen on 12/5/20.
//

#ifndef PROMPT_AVLTREE_H
#define PROMPT_AVLTREE_H

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
    void ll_Rotation(std::shared_ptr<BSTNode> &node);
    void lr_Rotation(std::shared_ptr<BSTNode> &node);
    void rl_Rotation(std::shared_ptr<BSTNode> &node);
    void rr_Rotation(std::shared_ptr<BSTNode> &node);
    void update(std::shared_ptr<BSTNode> lastNode);
};


#endif //PROMPT_AVLTREE_H
