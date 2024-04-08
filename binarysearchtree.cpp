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

    bool find(int data){
        Node *current = this->root;
        while (true){
            if (current == nullptr) return false;
            else if (data < current->data) current = current->left;
            else if (data > current->data) current = current->right;
            else return true;
        }
    }

    static void lrr(Node *node){
        if (node == nullptr) return;
        lrr(node->left);
        cout << node->data << ' ';
        lrr(node->right);
    }

    void print(){
        lrr(this->root);
        cout << endl;
    }
};

// ----------------------------------------------------------------------------------------------
void help(){
    cout << "You have a BinaryTree, possible commands:";
    cout << "\n--help (show ALL commands)";
    cout << "\n--push 'count' 'elements' (push 'count' elements to BinaryTree, ONLY integer)";
    cout << "\n--find 'elem' ('Yes' if 'elem' in BinaryTree else 'No')";
    cout << "\n--show (show BinaryTree)";
    cout << "\n--exit (exit the PROGRAM)\n\n";
}

void push(BinaryTree& bt){
    int count;
    if (scanf("%d", &count) != 1) {
        cout << "\n'count' should be integer\n";
        return;
    }
    int element;
    for (int i = 0; i < count; ++i) {
        if (scanf("%d", &element) != 1){
            cout << "\n'elements' should be integer\n";
            break;
        }
        bt.push(new Node(element));
    }
    cout << "\nBinaryTree: ";
    bt.print();
}

void find(BinaryTree& bt){
    int element;
    if (scanf("%d", &element) != 1) {
        cout << "\n'elem' should be integer\n";
        return;
    }
    bt.find(element) ? cout << "\nYes\n" : cout << "\nNo\n";
}

void show(BinaryTree& bt){
    cout << "\nBinaryTree: ";
    bt.print();
}

void doCommand(string& command, BinaryTree& bt){
    if (command == "--help") help();
    else if (command == "--push") push(bt);
    else if (command == "--find") find(bt);
    else if (command == "--show") show(bt);
    else cout << "\nNO such command\n";
}

// ----------------------------------------------------------------------------------------------
int main(){
    BinaryTree bt = BinaryTree();
    help();
    string command;
    while (true){
        cin >> command;
        if (command == "--exit") {
            cout << "\nThe PROGRAM is exited\n";
            break;
        } else doCommand(command, bt);
    }
    return 0;
}
