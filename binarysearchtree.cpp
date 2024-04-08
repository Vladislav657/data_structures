#include <iostream>

using namespace std;

class Node{
public:
    int data;
    Node *left;
    Node *right;

    explicit Node(int data){
        this->data = data;
        this->left = this->right = nullptr;
    }
};

class BinaryTree{
private:
    Node *root;

public:
    explicit BinaryTree(Node *root = nullptr){
        this->root = root;
    }

    void push(Node *node){
        if (this->root == nullptr) this->root = node;
        Node *current = this->root;
        while (true){
            if (node->data < current->data){
                if (current->left == nullptr){
                    current->left = node;
                    break;
                } else current = current->left;
            } else if (node->data > current->data){
                if (current->right == nullptr){
                    current->right = node;
                    break;
                } else current = current->right;
            } else break;
        }
    }

    Node *get(int data){
        Node *current = this->root;
        while (true){
            if (current == nullptr || data == current->data) return current;
            else if (data < current->data) current = current->left;
            else if (data > current->data) current = current->right;
        }
    }
};

void doCommand(string& command);

int main(){
    string command;
    while (true){
        cin >> command;
        if (command == "--exit") {
            cout << "\nThe PROGRAM is exited\n";
            break;
        } else doCommand(command);
    }
    return 0;
}
