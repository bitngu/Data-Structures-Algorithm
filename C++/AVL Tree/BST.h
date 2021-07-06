#include <memory>
#include <string>
#include "json.hpp"
class BST;

class BSTNode {
 public:
 	BSTNode(int key);
 	BSTNode(int key, std::weak_ptr<BSTNode> parent);
 	bool IsLeaf() const;
 	bool IsMissingChild() const;
 	bool HasLeftChild() const;
 	bool HasRightChild() const;
 	void DeleteChild(std::shared_ptr<BSTNode> v);
 	void ReplaceChild(std::shared_ptr<BSTNode> v, std::shared_ptr<BSTNode> u);

 	//getters
    int getKey() const;
    std::weak_ptr<BSTNode> getParent() const;
    std::shared_ptr<BSTNode> getLeft() const;
    std::shared_ptr<BSTNode> getRight() const;
    int getHeight() const;
    int getBalanceFactor() const;
    bool getisRoot_() const;

    //setters
    void setParent(const std::weak_ptr<BSTNode> &parent);
    void setLeft(const std::shared_ptr<BSTNode> &left);
    void setRight(const std::shared_ptr<BSTNode> &right);
    void setHeight(int height);
    void setBalanceFactor(int balanceFactor);
    void setIsRoot(bool isRoot);


private:
  int key_;
  bool isRoot_;
  int height_;
  int balanceFactor_;
  std::weak_ptr<BSTNode> parent_;
  std::shared_ptr<BSTNode> left_;
  std::shared_ptr<BSTNode> right_;

  friend BST;
}; // class BSTNode


class BST {
 public:
 	BST();
 	void Insert(int key);
 	bool Delete(int key);
 	std::shared_ptr<BSTNode> Find(int key) const;
 	nlohmann::json JSON() const;
 	size_t size() const;
 	bool empty() const;
 	int DeleteMin();

    void setRoot(const std::shared_ptr<BSTNode> &root);

private:
	void DeleteLeaf(std::shared_ptr<BSTNode> currentNode);
	int DeleteMin(std::shared_ptr<BSTNode> currentNode);
 	std::shared_ptr<BSTNode> root_;
 	size_t size_;
}; // class BST