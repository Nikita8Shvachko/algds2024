#ifndef TREAP_H
#define TREAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int key, priority;
    struct Node *left, *right, *parent;
};

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->priority = rand() % 100;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void rotateRight(struct Node **root, struct Node *x) {
    struct Node *y = x->left;
    x->left = y->right;
    if (y->right) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent) {
        *root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void rotateLeft(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

struct Node* insert(struct Node *root, int key) {

    struct Node *temp = newNode(key);


    if (!root) return temp;


    struct Node *curr = root, *parent = NULL;
    while (curr) {
        parent = curr;
        if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }


    temp->parent = parent;

    if (!parent) {
        root = temp;
    } else if (key < parent->key) {
        parent->left = temp;
    } else {
        parent->right = temp;
    }


    while (temp->parent && temp->priority > temp->parent->priority) {
        if (temp == temp->parent->left) {
            rotateRight(&root, temp->parent);
        } else {
            rotateLeft(&root, temp->parent);
        }
    }

    return root;
}
struct Node* erase(struct Node* root, int key) {
    struct Node* curr = root;
    struct Node* parent = NULL;


    while (curr && (curr->key != key)) {
        parent = curr;
        if (key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }


    if (!curr) return root;


    while (curr->left || curr->right) {
        if (!curr->right || (curr->left && curr->left->priority > curr->right->priority)) {
            rotateRight(root, curr);
            parent = curr;
            curr = curr->right;
        } else {
            rotateLeft(root, curr);
            parent = curr;
            curr = curr->left;
        }
    }


    if (parent) {
        if (parent->left == curr) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else {
        root = NULL;
    }

    free(curr);

    return root;
}

void printTreap(struct Node *root) {
    if (!root) {
        return;
    }
    printTreap(root->left);
    printf("%d \n", root->key);
    printTreap(root->right);
}

#endif // TREAP_H