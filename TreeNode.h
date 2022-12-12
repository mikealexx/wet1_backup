#ifndef TreeNodeID_h
#define TreeNodeID_h

#include <memory>
using namespace std;

template <class T, class S>
class TreeNode {
public:
    shared_ptr<T> data;
    S key;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode();
    TreeNode(shared_ptr<T> data, const S& key);
    TreeNode(const TreeNode& other);
    ~TreeNode() = default;
    TreeNode& operator=(const TreeNode& other);

};

template <class T, class S>
TreeNode<T, S>::TreeNode():
    data(nullptr),
    key(),
    left(nullptr),
    right(nullptr),
    height(1)
{}

/*
template <class T, class S>
TreeNode<T, S>::~TreeNode() {
    this->data.reset();
}
*/

template <class T, class S>
TreeNode<T, S>::TreeNode(shared_ptr<T> data, const S& key):
    data(data),
    key(key),
    left(nullptr),
    right(nullptr),
    height(1)
{}

template<class T, class S>
TreeNode<T, S>::TreeNode(const TreeNode<T, S>& other):
    data(shared_ptr<T>(other.data)),
    key(other.key),
    left(nullptr),
    right(nullptr),
    height(1)
{}

template <class T, class S>
TreeNode<T, S>& TreeNode<T, S>::operator=(const TreeNode<T, S>& other) {
    this->data = shared_ptr<T>(other.data);
    this->key = other->key;
    this->left = nullptr;
    this->right = nullptr;
    this->height = other->height;
    return *this;
}

#endif