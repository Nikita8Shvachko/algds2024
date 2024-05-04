#include "treap.h"
#include <gtest/gtest.h>
#include <iostream>
bool isBST(Node* node, Node* l=nullptr, Node* r=nullptr) {
    if (node == nullptr)
        return true;
    if (l != nullptr && node->key <= l->key)
        return false;
    if (r != nullptr && node->key >= r->key)
        return false;
    return isBST(node->left, l, node) && isBST(node->right, node, r);
}

bool isHeap(Node* node) {
    if (node == nullptr)
        return true;
    if (node->left != nullptr && node->left->priority > node->priority)
        return false;
    if (node->right != nullptr && node->right->priority > node->priority)
        return false;
    return isHeap(node->left) && isHeap(node->right);
}

TEST(TreapTest, InsertionTest) {
Node* root = nullptr;
root = insert(root, 4);
root = insert(root, 2);
root = insert(root, 6);
root = insert(root, 1);
root = insert(root, 3);
root = insert(root, 5);
root = insert(root, 7);

ASSERT_TRUE(isBST(root));
ASSERT_TRUE(isHeap(root));
}

TEST(TreapTest, DeletionTest) {
Node* root = nullptr;
root = insert(root, 4);
root = insert(root, 2);
root = insert(root, 6);
root = insert(root, 1);
root = insert(root, 3);
root = insert(root, 5);
root = insert(root, 7);

root = erase(root, 4);

ASSERT_TRUE(isBST(root));
ASSERT_TRUE(isHeap(root));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}
