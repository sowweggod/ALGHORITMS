#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    int numCount = 0;
    string* phNum = new string [numCount];
    Node* right;
    Node* left;
};

Node* CreateNode(string name, int numCount, string phNum[]) {
    Node* data = new Node;
    data->name = name;
    data->numCount = numCount;
    data->phNum = new string[numCount];
    for (int i = 0; i < numCount; i++) {
        data->phNum[i] = phNum[i];
    }
    data->right = nullptr;
    data->left = nullptr;

    return data;
}

void Insert(Node* person, int numCount, string phNum[], string name) {
    if (person->name > name) {
        if (person->left != nullptr) {
            Insert(person->left, numCount, phNum, name);
        }
        else {
            person->left = CreateNode(name, numCount, phNum);
        }
    }
    else {
        if (person->right != nullptr) {
            Insert(person->right, numCount, phNum, name);
        }
        else {
            person->right = CreateNode(name, numCount, phNum);
        }
    }
}



Node* FindNode(Node* person, string name) {
    if (person == nullptr || person->name == name) {
        return person;
    }
    if (name > person->name) {
        return FindNode(person->right, name);
    }
    else {
        return FindNode(person->left, name);
    }
}


void DeleteNode(Node* root, string name) {
    Node* curr = root;
    Node* parent = NULL;
    while (curr != NULL && curr->name != name) {
        parent = curr;
        if (curr->name > name) {
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
        string successorName = successor->name;
        DeleteNode(root, successorName);
        curr->name = successorName;
    }
}




void Lobby(Node* root) {
    cout << "Which operation do you want to do? " << endl;
    cout << "1. Add a person. " << endl;
    cout << "2. Find person." << endl;
    cout << "3. Delete person. " << endl;
    cout << "4. Exit. " << endl;

    int operation = 0;

    cin >> operation;
    

    if (operation == 1) {
        cout << "How many people do you want to add? " << endl;
        int people = 0;
        cin >> people;
        for (int i = 0; i < people; i++) {
            string name = "";
            cout << "Enter person's name: " << endl;
            cin >> name;
            cout << "How many phone numbers does person have? " << endl;
            int numCount = 0;
            cin >> numCount;
            
            string* phNum = new string[numCount];
            cout << "Enter numbers: " << endl;

            for (int j = 0; j < numCount; j++) {
                cin >> phNum[j];
            }
            if (i == 0 && root != NULL){
                root = CreateNode(name, numCount, phNum);
            }
            else {
                Insert(root, numCount, phNum, name);
            }
            cout << "Person was added. " << endl;
        }
        Lobby(root);
    }
    else if (operation == 2) {
        cout << "Enter person's name: " << endl;
        string find = "";
        cin >> find;
        Node* info = new Node;
        info = FindNode(root, find);
        if (info == NULL) {
            cout << "No such person in contacts. " << endl;
        }
        else {
            cout << "Name: " << info->name << endl;
            for (int i = 0; i < info->numCount; i++) {
                cout << "Phone number " << i + 1 << ":" << info->phNum[i] << endl;
            }
        }
        Lobby(root);
    }
    else if (operation == 3) {
        cout << "Which person do you want to delete? " << endl;
        string name = "";
        cin >> name;
        DeleteNode(root, name);
        Lobby(root);
        
    }
    else if (operation == 4) {
        
    }
    else {
        cout << "No such operation. " << endl;
        Lobby(root);
    }
}


int main() {
    Node* root = new Node;
    Lobby(root);
   
}