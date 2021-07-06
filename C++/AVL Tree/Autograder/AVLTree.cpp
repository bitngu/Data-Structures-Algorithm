//
// Created by Bi Nguyen on 12/5/20.
//

#include "AVLTree.h"

AVLTree::AVLTree(const std::string &filename) {
    std::ifstream fileContent{filename};
    nlohmann::json jsonContent;
    fileContent >> jsonContent;
    //need to insert item, and then somehow keep the item that i just inserted and go up to parent and update height and bf

    for (auto itr = jsonContent.begin(); itr != --jsonContent.end(); ++itr) {
        avl.Insert((*itr)["key"]);
        std::shared_ptr<BSTNode> recentInsertedNode = avl.Find((*itr)["key"]);
        //don't want to update when inserting the root;
        if(recentInsertedNode->getisRoot_()){
            continue;
        }
        auto lastNode = recentInsertedNode->getParent().lock();
        update(lastNode);//update the height and balance factor of nodes going up to the parent;
        //So each time i insert i have to check from the node i just added to the root if there is an unbalance;
        while(!recentInsertedNode->getisRoot_()){
            if (recentInsertedNode->getBalanceFactor() > 1){
                //there is a right unbalance
                if (recentInsertedNode->getRight()->getBalanceFactor() >= 0){
                    //right-right unbalance, so need left-left rotation;
                    ll_Rotation(recentInsertedNode);
                } else{
                    //right-left unbalance so need to do left-right rotation
                    lr_Rotation(recentInsertedNode);
                }
            }else if(recentInsertedNode->getBalanceFactor() < -1){
                //there is  a left unbalance
                if(recentInsertedNode->getLeft()->getBalanceFactor() < 0){
                    //left-left unbalance so need a right-right rotation
                    rr_Rotation(recentInsertedNode);
                }else{
                    //left-right unbalance so need a right-left rotation
                    rl_Rotation(recentInsertedNode);
                }
            }
            recentInsertedNode = recentInsertedNode->getParent().lock();
            update(recentInsertedNode);
        }
    }

    fileContent.close();
}


void AVLTree::update(std::shared_ptr<BSTNode> lastNode) {
    //now i need to go up and update the value of the heights and balance factor
    //now i need to rotate

    int temp_LBF = -1;
    int temp_RBF = -1;
    int lh = 0;
    int rh = 0;
    while(!lastNode->getisRoot_()){
        //store the larger height between left and right subtree, need to increment cause I insert an element;
        //need to consider that either left or right is null;
        //Need to reset balance factor & height each iteration
        temp_LBF = -1;
        temp_RBF = -1;
        lh = 0;
        rh = 0;
        if (lastNode->getLeft() != nullptr && lastNode->getRight() != nullptr){
            temp_LBF = lastNode->getLeft()->getHeight();
            lh = temp_LBF;
            temp_RBF = lastNode->getRight()->getHeight();
            rh = temp_RBF;
        }else if (lastNode->getRight() != nullptr){
            temp_RBF = lastNode->getRight()->getHeight();
            rh = temp_RBF;
        }else if (lastNode->getLeft() != nullptr){
            temp_LBF = lastNode->getLeft()->getHeight();
            lh = temp_LBF;
        }
        lastNode->setHeight( (lh >= rh) ? ++lh : ++rh);
        lastNode->setBalanceFactor(temp_RBF - temp_LBF);
        lastNode = lastNode->getParent().lock();
    }
    //Need to up date the root;
    //this is neccessary cause while loop breaks when at root
    if(lastNode->getLeft() != nullptr && lastNode-> getRight() != nullptr){
        temp_LBF = lastNode->getLeft()->getHeight();
        temp_RBF = lastNode->getRight()->getHeight();
        lh = temp_LBF;
        rh = temp_RBF;
    }else if (lastNode->getRight() != nullptr){
        temp_RBF = lastNode->getRight()->getHeight();
        rh = temp_RBF;
    }else if (lastNode->getLeft() != nullptr){
        temp_LBF = lastNode->getLeft()->getHeight();
        lh = temp_LBF;
    }
    lastNode->setHeight((lh >= rh) ? ++lh : ++rh);
    lastNode->setBalanceFactor(temp_RBF - temp_LBF);

}


//need to know where to set the right vs left of the parent;
//when the address of parent's right == node then set the new node to right


void AVLTree::ll_Rotation(std::shared_ptr<BSTNode> &node) {
    auto b = node->getRight();
    if(node->getParent().lock()->getRight() == node){
        node->getParent().lock()->setRight(b);
    }else{
        node->getParent().lock()->setLeft(b);
    }
    b->setLeft(node);
    b->setHeight(1);
    b->setBalanceFactor(0);
    node->setRight(nullptr);
    node->setBalanceFactor(0);
    node->setHeight(0);
    node->setParent(std::weak_ptr<BSTNode>(b));

}

void AVLTree::rr_Rotation(std::shared_ptr<BSTNode> &node) {
    //assuming node is the node with unbalance factor;
    //Remember: need to update the balance factor and the height as well
    auto b = node->getLeft();
    if(node->getParent().lock()->getRight() == node){
        node->getParent().lock()->setRight(b);
    }else{
        node->getParent().lock()->setLeft(b);
    }
    b->setParent(node->getParent());
    b->setRight(node);
    b->setHeight(1);
    b->setBalanceFactor(0);
    node->setLeft(nullptr);
    node->setBalanceFactor(0);
    node->setHeight(0);
    node->setParent(std::weak_ptr<BSTNode>(b));

}


void AVLTree::lr_Rotation(std::shared_ptr<BSTNode> &node) {
  //assuming node is the node with unbalance factor;
  auto b = node->getRight();
  auto c = b->getLeft();
  if(node->getParent().lock()->getRight() == node){
      node->getParent().lock()->setRight(c);
  }else{
      node->getParent().lock()->setLeft(c);
  }
  c->setParent(node->getParent());
  c->setRight(b);
  c->setLeft(node);
  c->setHeight(1);
  c->setBalanceFactor(0);
  b->setLeft(nullptr);
  b->setBalanceFactor(0);
  b->setHeight(0);
  node->setBalanceFactor(0);
  node->setHeight(0);
  node->setRight(nullptr);
  node->setParent(  std::weak_ptr<BSTNode>(c));


}

void AVLTree::rl_Rotation(std::shared_ptr<BSTNode> &node) {
    auto b = node->getLeft();
    auto c = b->getRight();
    if(node->getParent().lock()->getRight() == node){
        node->getParent().lock()->setRight(c);
    }else{
        node->getParent().lock()->setLeft(c);
    }
    c->setParent(node->getParent());
    c->setLeft(b);
    c->setRight(node);
    c->setHeight(1);
    c->setBalanceFactor(0);
    b->setRight(nullptr);
    b->setBalanceFactor(0);
    b->setHeight(0);
    node->setHeight(0);
    node->setBalanceFactor(0);
    node->setLeft(nullptr);
    node->setParent(std::weak_ptr<BSTNode>(c));
}

nlohmann::json AVLTree::JSON() {
    return avl.JSON();

}


