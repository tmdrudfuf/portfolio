#ifndef KY_H
#define KY_H

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val);
};

class BinarySearchTree {
private:
    Node* root;
    void clearRecursive(Node* node);
    void preorderRecursive(Node* node, vector<int>& result);
    void inorderRecursive(Node* node, vector<int>& result);
    void postorderRecursive(Node* node, vector<int>& result);

public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(int val);
    Node* search(int val, vector<int>& path);
    void clear();
    vector<int> preorder();
    vector<int> inorder();
    vector<int> postorder();
};

#endif // KY_H