#include <stdio.h>
#include "treap.h"

int main() {

    struct Node *root = NULL;

    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 6);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 7);

    printf("Treap after insertion\n");
    printTreap(root);

    root = erase(root, 4);
    printf("Treap after erasing 4\n");
    printTreap(root);

    return 0;
}
