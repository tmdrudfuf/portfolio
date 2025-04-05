#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct Node {
    int key;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    shared_ptr<Node> parent;

    Node(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BinarySearchTree {
public:
    shared_ptr<Node> root;

    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(); } // Destructor calls clear to prevent memory leaks.
    //adding
    void insert(int key) {
        cout << "Adding " << key << endl;
        auto z = make_shared<Node>(key);
        shared_ptr<Node> x = root;
        shared_ptr<Node> y = nullptr;

        while (x != nullptr) {
            y = x;
            if (z->key < x->key) {
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
        else if (z->key < y->key) {
            y->left = z;
        }
        else {
            y->right = z;
        }
    }
    //searching 
    shared_ptr<Node> search(shared_ptr<Node> x, int k) {
        cout << "Looking for " << k << "... ";
        shared_ptr<Node> current = root;
        while (current != nullptr) {
            cout << current->key << " ";
            if (k == current->key) return current;
            if (k < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }
    //travesal method
    void preorder(shared_ptr<Node> n) {
        if (n != nullptr) {
            cout << n->key << " ";
            preorder(n->left);
            preorder(n->right);
        }
    }

    void inorder(shared_ptr<Node> n) {
        if (n != nullptr) {
            inorder(n->left);
            cout << n->key << " ";
            inorder(n->right);
        }
    }

    void postorder(shared_ptr<Node> n) {
        if (n != nullptr) {
            postorder(n->left);
            postorder(n->right);
            cout << n->key << " ";
        }
    }
    //clear
    void clear() {
        clearRecursive(root);
        root = nullptr;
        cout << "(tree deleted!)" << endl;
    }

private:
    // recursive
    void clearRecursive(shared_ptr<Node> node) {
        if (node != nullptr) {
            cout << "Processing node at address: " << node.get() << endl; // 주소 출력
            clearRecursive(node->left);
            clearRecursive(node->right);
            cout << "Node at address: " << node.get() << " processed." << endl; // 처리 완료 출력
            node = nullptr; // shared_ptr은 자동 삭제, 하지만 명시적으로 nullptr을 넣음
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    int numLines;
    file >> numLines;
    file.ignore();

    BinarySearchTree bst;

    for (int i = 0; i < numLines; ++i) {
        string line;
        getline(file, line);
        stringstream ss(line);
        string command;
        int key;
        ss >> command;

        if (command == "ADD") {
            ss >> key;
            bst.insert(key);
        }
        else if (command == "FIND") {
            ss >> key;
            if (bst.search(bst.root, key)) {
                cout << ": found" << endl;
            }
            else {
                cout << ": not found" << endl;
            }
        }
        else if (command == "INORDER") {
            cout << "INORDER: ";
            bst.inorder(bst.root);
            cout << endl;
        }
        else if (command == "PREORDER") {
            cout << "PREORDER: ";
            bst.preorder(bst.root);
            cout << endl;
        }
        else if (command == "POSTORDER") {
            cout << "POSTORDER: ";
            bst.postorder(bst.root);
            cout << endl;
        }
        else if (command == "CLEAR") {
            bst.clear();
        }
        else {
            cerr << "Error: Unknown command: " << command << endl;
            return 1;
        }
    }

    file.close();
    return 0;
}