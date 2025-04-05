#include "ky.h" // Changed include to "ky.h"

Node::Node(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    clear();
}

void BinarySearchTree::insert(int val) {
    Node* z = new Node(val);
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr) {
        root = z;
    }
    else if (z->data < y->data) {
        y->left = z;
    }
    else {
        y->right = z;
    }
}

Node* BinarySearchTree::search(int val, vector<int>& path) {
    Node* x = root;
    path.clear();
    while (x != nullptr && val != x->data) {
        path.push_back(x->data);
        if (val < x->data) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    return x;
}

void BinarySearchTree::clear() {
    clearRecursive(root);
    root = nullptr;
}

void BinarySearchTree::clearRecursive(Node* node) {
    if (node != nullptr) {
        clearRecursive(node->left);
        clearRecursive(node->right);
        delete node;
    }
}

vector<int> BinarySearchTree::preorder() {
    vector<int> result;
    preorderRecursive(root, result);
    return result;
}

void BinarySearchTree::preorderRecursive(Node* node, vector<int>& result) {
    if (node != nullptr) {
        result.push_back(node->data);
        preorderRecursive(node->left, result);
        preorderRecursive(node->right, result);
    }
}

vector<int> BinarySearchTree::inorder() {
    vector<int> result;
    inorderRecursive(root, result);
    return result;
}

void BinarySearchTree::inorderRecursive(Node* node, vector<int>& result) {
    if (node != nullptr) {
        inorderRecursive(node->left, result);
        result.push_back(node->data);
        inorderRecursive(node->right, result);
    }
}

vector<int> BinarySearchTree::postorder() {
    vector<int> result;
    postorderRecursive(root, result);
    return result;
}

void BinarySearchTree::postorderRecursive(Node* node, vector<int>& result) {
    if (node != nullptr) {
        postorderRecursive(node->left, result);
        postorderRecursive(node->right, result);
        result.push_back(node->data);
    }
}
