//
// Created by Bi Nguyen on 12/5/20.
//

#include "AVL.h"

int i = 0;
AVLTree::AVLTree(const std::string &filename) {
    std::ifstream fileContent{filename};
    nlohmann::json jsonContent;
    fileContent >> jsonContent;
    //need to insert item, and then somehow keep the item that i just inserted and go up to parent and update height and bf

    for (auto itr = jsonContent.begin(); itr != --jsonContent.end(); ++itr) {
        //insert key to bst tree
        avl.Insert((*itr)["key"]);
        //look for the key that was just inserted; maybe not the best approach since my prog is taking too long
        std::shared_ptr<BSTNode> recentInsertedNode = avl.Find((*itr)["key"]);
        //don't want to update when inserting the root;
        if (recentInsertedNode->getisRoot_()) {
            continue;
        }
        //since recent node has 0 on everything, we want to update the parent node
        std::shared_ptr<BSTNode> parent = recentInsertedNode->getParent().lock();
        update(parent);//update the height and balance factor of nodes going up to the parent;
        //So each time i insert i have to check from the node i just added to the root if there is an unbalance;
        while (!parent->getisRoot_()) {
            doRotations(parent);
            parent = parent->getParent().lock();
            update(parent);
        }
        //since while loop break at the root node need to make sure that i can rotate at the root
        doRotations(parent);
    }
    fileContent.close();
}

void AVLTree::update(std::shared_ptr<BSTNode> lastNode) {
    //now i need to go up and update the value of the heights and balance factor
    while(!lastNode->getisRoot_()){
        lastNode->setHeight(updateHeight(lastNode));
        lastNode->setBalanceFactor(updateBF(lastNode));
        lastNode = lastNode->getParent().lock();
    }
    //Need to up date the root;
    //this is neccessary cause while loop breaks when at root
    lastNode->setHeight(updateHeight(lastNode));
    lastNode->setBalanceFactor(updateBF(lastNode));
}

void AVLTree::ll_Rotation(std::shared_ptr<BSTNode> &a) {
    std::shared_ptr<BSTNode> b = a->getRight();
    a->setRight(nullptr);
    if(a->getisRoot_()){//rotating at the root
        b->setParent(std::weak_ptr<BSTNode>());
        avl.setRoot(b);
        b->setIsRoot(true);
        a->setIsRoot(false);
    }else if(a->getParent().lock()->getRight() == a){//rotating right subtree
        a->getParent().lock()->setRight(b);
        b->setParent(a->getParent());
    }else{//rotating left subtree
        a->getParent().lock()->setLeft(b);
        b->setParent(a->getParent());
    }

    if (b->HasLeftChild()){
        //if b has a left child then i need to place b's left child to b a's right child
        //b's right child is unchanged
        b->getLeft()->setParent(a);
        a->setRight(b->getLeft());
    }

    //set a's parent to b b
    a->setParent(std::weak_ptr<BSTNode>(b));
    //set b's left child to b a;
    //update heights and balance factor of a and b
    //c never changes
    b->setLeft(a);
    a->setHeight(updateHeight(a));
    a->setBalanceFactor(updateBF(a));
    b->setHeight(updateHeight(b));
    b->setBalanceFactor(updateBF(b));
}

void AVLTree::rr_Rotation(std::shared_ptr<BSTNode> &a) {
    std::shared_ptr<BSTNode> b = a->getLeft();
    //remove a's left child which is b
    a->setLeft(nullptr);
    if(a->getisRoot_()){//rotating at the root
        b->setParent(std::weak_ptr<BSTNode>());
        avl.setRoot(b);
        b->setIsRoot(true);
        a->setIsRoot(false);
    }else if(a->getParent().lock()->getRight() == a){//rotating right subtree
        a->getParent().lock()->setRight(b);
        b->setParent(a->getParent());
    }else{//rotating leftsubtree
        a->getParent().lock()->setLeft(b);
        b->setParent(a->getParent());
    }
    if(b->HasRightChild()){
        //if b has a right child than a's left should hold b's right child
        b->getRight()->setParent(a);
        a->setLeft(b->getRight());
    }
    //set a's parent to be b
    a->setParent(std::weak_ptr<BSTNode>(b));
    //set b's right child to be a
    b->setRight(a);
    //update heights and balance factor of a and b
    //c never changes
    a->setHeight(updateHeight(a));
    a->setBalanceFactor(updateBF(a));
    b->setHeight(updateHeight(b));
    b->setBalanceFactor(updateBF(b));

}


void AVLTree::rl_Rotation(std::shared_ptr<BSTNode> &a) {
    //assuming node is the node with unbalance factor;
    std::shared_ptr<BSTNode> b = a->getLeft();
    std::shared_ptr<BSTNode> c = b->getRight();
    a->setLeft(nullptr);//remove b as a's left child
    b->setRight(nullptr);//remove c as b's right child

    if (a->getisRoot_()) {//rotating at the root
        c->setParent(std::weak_ptr<BSTNode>());
        avl.setRoot(c);
        c->setIsRoot(true);
        a->setIsRoot(false);
    } else if (a->getParent().lock()->getRight() == a) {//rotating on the right subtree
        a->getParent().lock()->setRight(c);
        c->setParent(a->getParent());

    } else {//rotating on the left subtree
        a->getParent().lock()->setLeft(c);
        c->setParent(a->getParent());
    }

    //if c has left child; make c's left child be b's right child; don't necessarily have to remove c's left child from c, can just do it later
    //if c doesn't have a left child then nothing needs to be done
    if (c->HasLeftChild()) {
        //make c's left be a's child
        c->getLeft()->setParent(std::weak_ptr<BSTNode>(b));
        //set a's right to  be c's left child
        b->setRight(c->getLeft());
    }
    if (c->HasRightChild()) {
        //if c has a right child, then make c's right child be a's left child;
        c->getRight()->setParent(std::weak_ptr<BSTNode>(a));
        a->setLeft(c->getRight());
    }

    //update a and b's height and balance factor
    a->setHeight(updateHeight(a));
    a->setBalanceFactor(updateBF(a));
    b->setHeight(updateHeight(b));
    b->setBalanceFactor(updateBF(b));

    //set  a and b's parent to be c
    b->setParent(std::weak_ptr<BSTNode>(c));
    a->setParent(std::weak_ptr<BSTNode>(c));
    //update c's left child and c's right child;
    c->setRight(a);
    c->setLeft(b);
    //update c's height and balance factor
    c->setHeight(updateHeight(c));
    c->setBalanceFactor(updateBF(c));
}

void AVLTree::lr_Rotation(std::shared_ptr<BSTNode> &a) {

    std::shared_ptr<BSTNode> b = a->getRight();
    std::shared_ptr<BSTNode> c = b->getLeft();
    //remove a's right child which is b
    a->setRight(nullptr);
    //removing b's left child which is c
    b->setLeft(nullptr);

    if (a->getisRoot_()) {//rotating at the root
        //set root to new node
        c->setParent(std::weak_ptr<BSTNode>());
        avl.setRoot(c);
        c->setIsRoot(true);
        a->setIsRoot(false);
    } else if (a->getParent().lock()->getRight() == a) {
        //set the parent of the current to be new node's parent
        a->getParent().lock()->setRight(c);
        c->setParent(a->getParent());
    } else {
        a->getParent().lock()->setLeft(c);
        c->setParent(a->getParent());
    }
    //If c has a left child then make a's right be c's left
    if (c->HasLeftChild()) {
        c->getLeft()->setParent(std::weak_ptr<BSTNode>(a));
        a->setRight(c->getLeft());
    }
    //If c has a right child then make b's left be c's right and update the height
    if (c->HasRightChild()) {
        //if c has a right child
        c->getRight()->setParent(std::weak_ptr<BSTNode>(b));
        b->setLeft(c->getRight());
    }
    //update a and b's height and balance factor
    a->setHeight(updateHeight(a));
    a->setBalanceFactor(updateBF(a));
    b->setHeight(updateHeight(b));
    b->setBalanceFactor(updateBF(b));
    //set  a and b's parent to be c
    b->setParent(std::weak_ptr<BSTNode>(c));
    a->setParent(std::weak_ptr<BSTNode>(c));
    //update c's left child and c's right child;
    c->setRight(b);
    c->setLeft(a);
    //update c's height and balance factor
    c->setHeight(updateHeight(c));
    c->setBalanceFactor(updateBF(c));

}

nlohmann::json AVLTree::JSON() {
    return avl.JSON();

}

void AVLTree::doRotations(std::shared_ptr<BSTNode> recentInsertedNode) {
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
}

int AVLTree::updateHeight(const std::shared_ptr<BSTNode> &currentNode) {
    //Assuming there is no child
    //when there is no left or right child return 0

    if(!(currentNode->IsMissingChild())){
        return  0;
    }
    int leftHeight = 0;
    int rightHeight = 0;
    //if there is a left child, get its height
    if(currentNode->HasLeftChild()){
        leftHeight = currentNode->getLeft()->getHeight();
    }
    //if there is a right child, get its height
    if (currentNode->HasRightChild()){
        rightHeight = currentNode->getRight()->getHeight();
    }

    //update current height by selecting the larger height tree. Since current node is the parent, the height must be added 1
    return (leftHeight > rightHeight) ? ++leftHeight : ++rightHeight;
}

int AVLTree::updateBF(const std::shared_ptr<BSTNode> &currentNode) {
    //Assuming there is no child
    int bfLeft = -1;
    int bfRight = -1;
    //If there is a left child, update the left balance factor as the height
    if(currentNode->HasLeftChild()){
        bfLeft = currentNode->getLeft()->getHeight();
    }
    if(currentNode->HasRightChild()){
        bfRight = currentNode->getRight()->getHeight();
    }
   return bfRight - bfLeft;
}