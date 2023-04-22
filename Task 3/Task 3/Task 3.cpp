#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

int height(Node* node) {
    if (!node) {
        return 0;
    }
    else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        if (leftHeight > rightHeight) {
            return (leftHeight + 1);
        }
        else {
            return (rightHeight + 1);
        }
    }
}

int balanceFactor(Node* node) {
    if (!node) {
        return 0;
    }
    else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return (leftHeight - rightHeight);
    }
}

Node* newNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node* insert(Node* node, int data) {
    if (!node) {
        return newNode(data);
    }
    else {
        if (data <= node->data) {
            node->left = insert(node->left, data);
        }
        else {
            node->right = insert(node->right, data);
        }
        return node;
    }
}

void printBalanceFactors(Node* node) {
    if (node) {
        printBalanceFactors(node->left);
        cout << "Balance factor for node " << node->data << " is " << balanceFactor(node) << endl;
        printBalanceFactors(node->right);
    }
}

int main() {
    Node* root = nullptr;
    root = insert(root, 4);
    insert(root, 2);
    insert(root, 1);
    insert(root, 3);
    insert(root, 6);
    insert(root, 5);
    insert(root, 7);
    printBalanceFactors(root);
    return 0;
}
