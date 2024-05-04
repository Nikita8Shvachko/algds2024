#include <iostream>
#include "treap.h"

using namespace std;

int main() {

    Node *root = nullptr;


    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 6);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 7);

    cout << "Treap after insertion" << endl;
    printTreap(root);


    root = erase(root, 4);
    cout << "Treap after erasing 4" << endl;
    printTreap(root);

    return 0;
}