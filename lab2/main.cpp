#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

struct Node {
    int key, priority;
    Node *left, *right, *parent;

    Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr), parent(nullptr) {}
};

void rotateRight(Node *&root, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent) {
        root = y; // x was the root
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void rotateLeft(Node *&root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent) {
        root = y; // x was the root
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}


Node* insert(Node* root, int key) {
    Node* newNode = new Node(key);
    if (!root) return newNode;

    Node* curr = root;
    Node* parent = nullptr;
    while (curr) {
        parent = curr;
        if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (!parent) {
        return newNode; // Treap is empty
    }

    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    newNode->parent = parent;

    // Bubble up the new node to maintain the heap property
    while (newNode->parent && newNode->priority > newNode->parent->priority) {
        if (newNode == newNode->parent->left) {
            rotateRight(root, newNode->parent);
        } else {
            rotateLeft(root, newNode->parent);
        }
    }


    return (parent == nullptr) ? newNode : root;
}


Node* erase(Node*& root, int key) {
    Node* curr = root;
    Node* parent = nullptr;

    // Find the node to be deleted
    while (curr && curr->key != key) {
        parent = curr;
        if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (!curr) return root; // Key not found

    // Bubble down the node to be deleted
    while (curr->left || curr->right) {
        if (!curr->right || (curr->left && curr->left->priority > curr->right->priority)) {
            rotateRight(root, curr);
            curr = curr->parent;
        } else {
            rotateLeft(root, curr);
            curr = curr->parent;
        }
    }

    // Now the node can be safely deleted
    if (parent) {
        if (parent->left == curr) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
    } else {
        root = nullptr;
    }
    delete curr;

    return root;
}


void printTreap(Node *root) {
    if (!root) {
        return;
    }
    printTreap(root->left);
    cout << root->key << " " << endl;
    printTreap(root->right);
}

int main() {

    Node *root = nullptr;

    // Insert nodes into the treap
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 6);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 7);

    // Display the treap
    cout << "Treap after insertion:" << endl;
    printTreap(root);

    // Erase a node from the treap
    root = erase(root, 4);
    cout << "Treap after erasing 4:" << endl;
    printTreap(root);

    return 0;
}
