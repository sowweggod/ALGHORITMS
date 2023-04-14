#include <iostream>
#include <string>
using namespace std;

struct Node {
    int koki;
    Node* right;
    Node* left;
};

Node* CreateNode(int value) {
    Node* moki = new Node;
    moki->koki = value;
    moki->right = nullptr;
    moki->left = nullptr;
    return moki;
}

void Insert(Node* root, int value) {
    if (root->koki > value) {
        if (root->left != nullptr) {
            Insert(root->left, value);
        }
        else {
            root->left = CreateNode(value);
        }
    }
    else {
        if (root->right != nullptr) {
            Insert(root->right, value);
        }
        else {
            root->right = CreateNode(value);
        }
    }
}

void PrintTree(Node* root) {
    if (root != nullptr) {
        PrintTree(root->left);
        cout << root->koki << " ";
        PrintTree(root->right);
    }
}


int main() {
    Node* root = CreateNode(8);
    int mas[6] = { 3, 5, 10, 12, 11, 17 };
    for (int i = 0; i < 6; i++) {
        Insert(root, mas[i]);
    }
    PrintTree(root);
}
