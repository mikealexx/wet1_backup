#ifndef AVLTree_h
#define AVLTree_h

#include "TreeNode.h"

template<class T, class S>
class AVLTree {
        //calculate max
        static int max(int a, int b) {
            return (a>b) ? a : b;
        }

        //calculate height of a node
        static int height(const TreeNode<T, S>* node) {
            if(node == nullptr) {
                return 0;
            }
            if (node->left == nullptr){
                if(node->right == nullptr) 
                    return 1;
                return node->right->height + 1;
            }
            if (node->right == nullptr)
                return node->left->height + 1;

            return AVLTree::max(node->left->height, node->right->height) + 1;
        }

        //calculate balance factor of a node
        static int balanceFactor(const TreeNode<T, S>* node) {
            if(node == nullptr) {
                return 0;
            }
            return AVLTree::height(node->left) - AVLTree::height(node->right);
        }

        //rebalance the tree using rotations
        static TreeNode<T, S>* balanceTree(TreeNode<T, S>* root) {
            if(root == nullptr) {
                return nullptr;
            }
            root->height = AVLTree::height(root);
            int balance = AVLTree::balanceFactor(root);
            if(balance == 2) {
                if(AVLTree::balanceFactor(root->left) >= 0) { //Left Left Rotation
                    return AVLTree::LLRotation(root);
                }
                else { //left right rotation
                    return AVLTree::LRRotation(root);
                }
            }
            if(balance == -2) {
                if(AVLTree::balanceFactor(root->right) <= 0) { //right right rotation
                    return AVLTree::RRRotation(root);
                }
                else { //right left rotation
                    return AVLTree::RLRotation(root);
                }
            }
            return root;
        }
        
        //A function for deleting a node from a BST tree, used later for remove
        static TreeNode<T, S>* deleteNode(TreeNode<T, S>* root, const S& key){
            if (root == nullptr){
                return root;
            }

            if (key < root->key){
                root->left = deleteNode(root->left, key);
            }

            else if (key > root->key){
                root->right = deleteNode(root->right, key);
            }

            else{

                if (root->left == nullptr && root->right == nullptr) {
                    delete(root);
                    return nullptr;
                }
                
                TreeNode<T, S>* temp;
                if (root->left == nullptr) {
                    temp = root;
                    root = root->right;
                    delete(temp);
                    return root;
                }

                if (root->right == nullptr) {
                    temp = root;
                    root = root->left;
                    delete(temp);
                    return root;
                }

                temp = minNode(root->right);
                root->key = temp->key;
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->key);
            }

            return root;
        }
        
        //return predecessor
        static TreeNode<T, S>* minNode(TreeNode<T, S>* node) {
            TreeNode<T, S>* current = node;
            while (current->left != nullptr)
                current = current->left;
            return current;
        }

        //return successor
        static TreeNode<T, S>* maxNode(TreeNode<T, S>* node) {
            TreeNode<T, S>* current = node;
            while (current->right != nullptr)
                current = current->right;
            return current;
        }

        //right right rotation
        static TreeNode<T, S>* RRRotation(TreeNode<T, S>* root) {
            TreeNode<T, S>* oldRoot = root;
            TreeNode<T, S>* newRoot = root->right;
            oldRoot->right = newRoot->left;
            newRoot->left = oldRoot;
            oldRoot->height = height(oldRoot);
            newRoot->height = height(newRoot);
            return newRoot;
        }

        //left left rotation
        static TreeNode<T, S>* LLRotation(TreeNode<T, S>* root) {
            TreeNode<T, S>* oldRoot = root;
            TreeNode<T, S>* newRoot = root->left;
            oldRoot->left = newRoot->right;
            newRoot->right = oldRoot;
            oldRoot->height = height(oldRoot);
            newRoot->height = height(newRoot);
            return newRoot;
        }

        //left right rotation
        static TreeNode<T, S>* LRRotation(TreeNode<T, S>* root) {
            TreeNode<T, S>* oldRoot = root;
            TreeNode<T, S>* node = root->left;
            TreeNode<T, S>* newRoot = root->left->right;
            oldRoot->left = newRoot->right;
            node->right = newRoot->left;
            newRoot->right = oldRoot;
            newRoot->left = node;
            oldRoot->height = height(oldRoot);
            node->height = height(node);
            newRoot->height = height(newRoot);
            return newRoot;
        }

        //right left rotation
        static TreeNode<T, S>* RLRotation(TreeNode<T, S>* root) {
            TreeNode<T, S>* oldRoot = root;
            TreeNode<T, S>* node = root->right;
            TreeNode<T, S>* newRoot = root->right->left;
            oldRoot->right = newRoot->left;
            node->left = newRoot->right;
            newRoot->left = oldRoot;
            newRoot->right = node;
            oldRoot->height = height(oldRoot);
            node->height = height(node);
            newRoot->height = height(newRoot);
            return newRoot;
        }

        static TreeNode<T, S>* insertHelper(TreeNode<T, S>* root, shared_ptr<T> data, const S& key) {
            if(root == nullptr) {
                return new TreeNode<T, S>(data, key);
            }
            if(key < root->key) { //locate correct insertion position
                root->left = insertHelper(root->left, data, key);
            }
            else if (key > root->key) { //REMOVE = LATER - DONT FORGET
                root->right = insertHelper(root->right, data, key);
            }
            else { //same keys - illegal
                throw AVLTree::KeyAlreadyExists();
            }
            return AVLTree::balanceTree(root);
        }

        static TreeNode<T, S>* removeHelper(TreeNode<T, S>* root, const S& key) {
            return AVLTree::balanceTree(deleteNode(root, key));
        }

        static TreeNode<T, S>* findHelper(TreeNode<T, S>* root, const S& key){
            if (root == nullptr) {
                throw AVLTree<T, S>::NodeNotFound();
            }

            if (key < root->key){
                return findHelper(root->left, key);
            }

            else if (key > root->key){
                return findHelper(root->right, key);
            }

            return root;
        }

        

        static void mergeArrays(TreeNode<T, S> * arr1[], TreeNode<T, S> * arr2[], int arr1_size, int arr2_size, TreeNode<T, S> * arr3[]) {
            int i = 0, j = 0, k = 0;
            while (i < arr1_size && j < arr2_size) {
                if (arr1[i]->key < arr2[j]->key) {
                    arr3[k++] = arr1[i++];
                }
                else {
                    arr3[k++] = arr2[j++];
                }
            }
            while (i < arr1_size) {
                arr3[k++] = arr1[i++];
            }
            while (j < arr2_size) {
                arr3[k++] = arr2[j++];
            }

            
        }

        static TreeNode<T, S>* sortedArrayToAVLTree(TreeNode<T, S> * arr[], int start, int end) {
            if (start > end) {
                return nullptr;
            }
            int mid = (start + end)/2;
            TreeNode<T, S>* root = new TreeNode<T, S>();
            root->data = shared_ptr<T>(arr[mid]->data);
            root->key = arr[mid]->key;
            TreeNode<T, S>* newLeft = sortedArrayToAVLTree(arr, start, mid - 1);
            TreeNode<T, S>* newRight = sortedArrayToAVLTree(arr, mid + 1, end);
            root->left = newLeft;
            root->right = newRight;
            return root;
        }

    public:
        TreeNode<T, S>* root;
        int size;
        int getSize() const;
        AVLTree();
        ~AVLTree();
        void insert(shared_ptr<T> data, const S& key);
        void remove(const S& key);
        TreeNode<T, S>* findNode(const S& key);
        TreeNode<T, S>* findPredecessor(const S& key);
        TreeNode<T, S>* findSuccessor(const S& key);
        class KeyAlreadyExists : public std::exception{};
        class NodeNotFound : public std::exception{};

        static void merge(AVLTree<T, S> const &tree1, AVLTree<T, S> const &tree2, AVLTree<T, S> &merged) {
            int arr1_size = tree1.getSize();
            int arr2_size = tree2.getSize();
            int arr3_size = arr1_size + arr2_size;
            TreeNode<T, S>** arr1 = new TreeNode<T, S>* [arr1_size]; //first tree sorted array
            TreeNode<T, S>** arr2 = new TreeNode<T, S>* [arr2_size]; //second tree sorted array
            TreeNode<T, S>** arr3 = new TreeNode<T, S>* [arr3_size]; //sorted merged array of both trees
            AVLTree::treeToArray(arr1, tree1.root, 0);
            AVLTree::treeToArray(arr2, tree2.root, 0);
            AVLTree::mergeArrays(arr1, arr2, arr1_size, arr2_size, arr3);
            merged.root = sortedArrayToAVLTree(arr3, 0, arr3_size-1);
            merged.size = arr3_size;
            delete[] arr1;
            delete[] arr2;
            delete[] arr3;
        }

        //helper function for the D'CTOR
        static void destruct(TreeNode<T, S>* node){
            if (node != nullptr) {
                destruct(node->left);
                destruct(node->right);
                if(node->data != nullptr) {
                    node->data.reset();
                }
                delete node;
            }
            return;
        }

        static int treeToArray(TreeNode<T, S>* array[], TreeNode<T, S>* root, int i) {
            if(root == nullptr) {
                return i;
            }
            if(root->left != nullptr) {
                i = treeToArray(array, root->left, i);
            }
            array[i] = root;
            i++;
            if(root->right != nullptr) {
                i = treeToArray(array, root->right, i);
            }
            return i;
        }
};

template<class T, class S>
AVLTree<T, S>::AVLTree(): 
    root(nullptr),
    size(0)
{}

template<class T, class S>
int AVLTree<T, S>::getSize() const{
    return this->size;
}

template<class T, class S>
AVLTree<T, S>::~AVLTree() {
    AVLTree::destruct(this->root);
}

template<class T, class S>
void AVLTree<T, S>::insert(shared_ptr<T> data, const S& key) {
    this->root = insertHelper(this->root, data, key);
    this->size++;
}

template<class T, class S>
void AVLTree<T, S>::remove(const S& key) {
    this->root = removeHelper(this->root, key);
    this->size--;
}

template<class T, class S>
TreeNode<T, S>* AVLTree<T, S>::findNode(const S& key){
    return findHelper(this->root, key);
}

template<class T, class S>
TreeNode<T, S>* AVLTree<T, S>::findPredecessor(const S& key){   // find predecessor of node. find node, if it has a left son, 
    TreeNode <T, S>* node = AVLTree::findNode(key);             // find its max node and return it. otherwise, go back to the root
    if (node->left != nullptr){                                 // and go down the tree - right if key is bigger than current node's 
        return AVLTree<T, S>::maxNode(node->left);              // key and left otherwise.
    }
    TreeNode<T, S>* curr = this->root;
    TreeNode<T, S>* pre = nullptr;
    while (curr != nullptr && key != curr->key) {
        if (key > curr->key) {
            pre = curr;
            curr = curr->right;
        }
        else if (key < curr->key) {
            curr = curr->left;
        }
    }
    return pre;
}

template<class T, class S>
TreeNode<T, S>* AVLTree<T, S>::findSuccessor(const S& key){ // find successor of node. similar to the predecessor's algorithm. 
    TreeNode<T, S>* node = AVLTree::findNode(key);                       
    if (node->right != nullptr) {                           
        return AVLTree<T, S>::minNode(node->right);       
    }
    TreeNode<T, S>* curr = this->root;
    TreeNode<T, S>* succ = nullptr;
    while (curr != nullptr && key != curr->key) {
        if (key < curr->key){
            succ = curr;
            curr = curr->left;
        }
        else if (key > curr->key){
            curr = curr->right;
        }
    }
    return succ;
}

#endif