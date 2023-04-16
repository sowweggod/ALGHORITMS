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

Node* FindNode(Node* root, int value) {
    if (root == nullptr || root->koki == value) {
        return root;
    }
    if (value > root->koki) {
        return FindNode(root->right, value);
    }
    else {
        return FindNode(root->left, value);
    }
}

int DepthTree(Node* root) {
    if (root != NULL) {
        int LeftDepth = DepthTree(root->left);
        int RightDepth = DepthTree(root->right);
        return max(LeftDepth, RightDepth) + 1;
    }
    else {
        return 0;
    }
}

void DeleteNode(Node* root, int value) {
    Node* curr = root;
    Node* parent = NULL;
    while (curr != NULL && curr->koki != value) {
        parent = curr;
        if (curr->koki > value) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    if (curr == NULL) {
        return;
    }

    bool isLeftChild = (parent != NULL && curr == parent->left);

    if (curr->left == nullptr && curr->right == nullptr) {
        if (parent == NULL) {
            root = NULL;
        }
        else if (isLeftChild) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }

        delete curr;

    }
    else if (curr->left == nullptr || curr->right == nullptr) {
        Node* child = (curr->left != NULL) ? curr->left : curr->right;

        if (parent == NULL) {
            root = child;
        }
        else if (isLeftChild) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }

        delete curr;
    }
    else {
        Node* successor = curr->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        int successorValue = successor->koki;
        DeleteNode(root, successorValue);
        curr->koki = successorValue;
    }
}



int main() {
    Node* root = CreateNode(8);
    int mas[8] = { 3, 5, 1, 11, 10, 12, 9, 17 };
    for (int i = 0; i < 8; i++) {
        Insert(root, mas[i]);
    }
    cout << "Tree: ";
    PrintTree(root);
    cout << endl;
    cout << "Found node (36): ";
    Node* found = FindNode(root, 36);
    if(found != NULL)
    {
        cout << found->koki << " " << found->left << " " << found->right << endl;
    }
    else
    {
        cout << "This element does not exist" << endl;
    }
    cout << "Depth of tree: ";
    cout << DepthTree(root) << endl;
    DeleteNode(root, 11);
    cout << "Tree without 11: ";
    PrintTree(root);
}
