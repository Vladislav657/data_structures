#include <iostream>

using namespace std;

class Char{
public:
    char data;
    Char *next;

    explicit Char(char data){
        this->data = data;
        this->next = nullptr;
    }
};

class Stack{
private:
    Char *head;

public:
    Stack(){
        this->head = nullptr;
    }

    void push(Char *ch){
        ch->next = this->head;
        this->head = ch;
    }

    Char *pop(){
        Char *ch = this->head;
        if (ch != nullptr){
            this->head = this->head->next;
            ch->next = nullptr;
        }
        return ch;
    }

    bool empty(){
        return this->head == nullptr;
    }

    void print(){
        Char *current = this->head;
        while (current != nullptr){
            cout << current->data << ' ';
            current = current->next;
        }
        cout << endl;
    }
};

// -----------------------------------------------------------------------------------------------------------------
class Node{
public:
    unsigned tag;
    char atom;
    Node *level;
    Node *next;

    Node(){
        this->tag = 0;
        this->atom = 0;
        this->level = this->next = nullptr;
    }

    explicit Node(char atom){
        this->tag = 1;
        this->atom = atom;
        this->level = this->next = nullptr;
    }
};

class LinearList{
private:
    static void push(Stack& exp, Node *current) {
        if (exp.empty()) return;
        char currChar = exp.pop()->data;
        if (current->tag == 0) {
            if (currChar == '(') current->level = new Node();
            else if (currChar == ')') return;
            else current->level = new Node(currChar);
            push(exp, current->level);
            if (exp.empty()) return;
            currChar = exp.pop()->data;
            if (currChar == '(') current->next = new Node();
            else if (currChar == ')') return;
            else current->next = new Node(currChar);
            push(exp, current->next);
        } else {
            if (currChar == '(') current->next = new Node();
            else if (currChar == ')') return;
            else current->next = new Node(currChar);
            push(exp, current->next);
        }
    }

    static void show(Node *current){
        if (current == nullptr) return;
        if (current->tag == 1){
            cout << current->atom;
        } else if (current->tag == 0){
            cout << '(';
            Node *node = current->level;
            while (node != nullptr){
                show(node);
                node = node->next;
            }
            cout << ')';
        }
    }

public:
    Node *head;

    LinearList(){
        this->head = new Node();
    }

    explicit LinearList(char atom){
        this->head = new Node(atom);
    }

    explicit LinearList(Node *node){
        this->head = node;
    }

    explicit LinearList(Stack& list){
        if (list.empty()){
            this->head = new Node();
            return;
        }
        list.pop();
        this->head = new Node();
        push(list, this->head);
    }

    bool empty() const{
        return this->head->tag == 0 && this->head->next == nullptr && head->level == nullptr;
    }

    bool atomic() const{
        return this->head->tag == 1 && this->head->next == nullptr;
    }

    LinearList *header(){
        if (this->empty() || this->atomic()) return nullptr;
        Node *node = head->level;
        head->level = head->level->next;
        node->next = nullptr;
        auto *lst = new LinearList(node);
        return lst;
    }

    void print() const{
        show(this->head);
        cout << endl;
    }
};

// -----------------------------------------------------------------------------------------------------------------
class TreeNode{
public:
    char data;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(char data = 0){
        this->data = data;
        this->left = this->right = nullptr;
    }
};

class BinaryTree{
private:
    static void load(TreeNode *current, LinearList *ll){
        if (ll->empty()) return;
        if (ll->atomic()) current->data = ll->head->atom;
        else{
            current->left = new TreeNode();
            load(current->left, ll->header());
            current->data = ll->header()->head->atom;
            current->right = new TreeNode();
            load(current->right, ll->header());
        }
    }

    static void input(TreeNode *current, string& exp){
        if (exp.size() == 1){
            current->data = exp[0];
            return;
        }
        string left, right;
        char op;
        bool found = false;
        int balance = 0;
        for (int i = 1; i < exp.size() - 1; ++i) {
            if (exp[i] == '(') balance++;
            else if (exp[i] == ')') balance--;
            else if (exp[i] == '*' || exp[i] == '/' || exp[i] == '+' || exp[i] == '-'){
                if (balance == 0 && !found){
                    op = exp[i];
                    found = true;
                    continue;
                }
            }
            found ? right.push_back(exp[i]) : left.push_back(exp[i]);
        }
        current->data = op;
        current->left =  new TreeNode();
        input(current->left, left);
        current->right =  new TreeNode();
        input(current->right, right);
    }

public:
    TreeNode *root;

    static string toString(TreeNode *node){
        string s;
        if (node == nullptr) return s;
        if (node->data >= 'a' && node->data <= 'z') return s + node->data;
        return '(' + toString(node->left) + node->data + toString(node->right) + ')';
    }

    static string getPostfix(TreeNode *node){
        string s;
        if (node == nullptr) return s;
        if (node->data >= 'a' && node->data <= 'z') return s + node->data;
        return getPostfix(node->left) + getPostfix(node->right) + node->data;
    }

    explicit BinaryTree(TreeNode *root = nullptr){
        this->root = root;
    }

    explicit BinaryTree(LinearList *ll){
        this->root = new TreeNode();
        load(this->root, ll);
    }

    explicit BinaryTree(string& exp){
        this->root = new TreeNode();
        input(this->root, exp);
    }

    bool empty() const{
        return this->root == nullptr;
    }

    bool one() const{
        return this->root != nullptr && this->root->left == nullptr && this->root->right == nullptr;
    }

    void print() const{
        cout << toString(this->root) << endl;
    }
};

// -----------------------------------------------------------------------------------------------------------------
bool isRight(string& exp) {
    if (exp[0] != '(' || exp[exp.size() - 1] != ')') return false;
    Stack balance = Stack();
    int levels[100];
    for (int& level : levels) level = 0;
    int level = -1;
    for (char i : exp) {
        if (i == '(') {
            balance.push(new Char(i));
            level++;
        }
        else if (i == '*' || i == '/' || i == '+' || i == '-'){
            levels[level]++;
        }
        else if (i == ')') {
            if (balance.pop() == nullptr || levels[level] != 1) return false;
            levels[level] = 0;
            level--;
        }
    }
    if (!balance.empty()) return false;
    int index = 0;
    for (int i = 1; i < exp.size() - 1; ++i) {
        if (exp[i] == '*' || exp[i] == '/' || exp[i] == '+' || exp[i] == '-') {
            if (index % 2 == 0 || exp[i - 1] == '(' || exp[i + 1] == ')') return false;
            index++;
        } else if (exp[i] >= 'a' && exp[i] <= 'z'){
            if (index % 2 == 1 || exp[i - 1] == ')' || exp[i + 1] == '(') return false;
            index++;
        } else if (exp[i] == '(' || exp[i] == ')') continue;
        else return false;
    }
    return true;
}

// -----------------------------------------------------------------------------------------------------------------
void help(){
    cout << "You can enter ARITHMETIC EXPRESSION and do different commands:\n\n";
    cout << "--help (show ALL COMMANDS)\n";
    cout << "--list 'exp' (load EXPRESSION 'exp' to LinearList)\n";
    cout << "--lt (load from LinearList to BinaryTree)\n";
    cout << "--tree 'exp' (load EXPRESSION 'exp' to BinaryTree)\n";
    cout << "--tl (load from BinaryTree to LinearList)\n";
    cout << "--pf (get POSTFIX from BinaryTree)\n";
    cout << "--show 'structure' (print BinaryTree '-t' or LinearList '-l')\n";
    cout << "--exit (exit the PROGRAM)\n";
    cout << "'exp' RIGHT ARITHMETIC EXPRESSION, example: '((a+b)/(a-c))'\n\n";
}

void list(LinearList& lst){
    string exp;
    cin >> exp;
    if (!isRight(exp)){
        cout << "\nWRONG expression\n";
        return;
    }
    Stack expStack = Stack();
    for (int i = (int)exp.size() - 1; i >= 0; --i) expStack.push(new Char(exp[i]));
    lst = LinearList(expStack);
    cout << "\nLinearList: ";
    lst.print();
}

void lt(LinearList& lst, BinaryTree& tr){
    tr = BinaryTree(&lst);
    cout << "\nBinaryTree: ";
    tr.print();
}

void tree(BinaryTree& tr){
    string exp;
    cin >> exp;
    if (!isRight(exp)){
        cout << "\nWRONG expression\n";
        return;
    }
    tr = BinaryTree(exp);
    cout << "\nBinaryTree: ";
    tr.print();
}

void tl(LinearList& lst, BinaryTree& tr){
    string exp = BinaryTree::toString(tr.root);
    Stack expStack = Stack();
    for (int i = (int)exp.size() - 1; i >= 0; --i) expStack.push(new Char(exp[i]));
    lst = LinearList(expStack);
    cout << "\nLinearList: ";
    lst.print();
}

void pf(BinaryTree& tr){
    string postfix = BinaryTree::getPostfix(tr.root);
    cout << "\nPostfix: " << postfix << endl;
}

void show(LinearList& lst, BinaryTree& tr){
    string structure;
    cin >> structure;
    if (structure == "-t"){
        cout << "\nBinaryTree: ";
        tr.print();
    } else if (structure == "-l"){
        cout << "\nLinearList: ";
        lst.print();
    } else cout << "\nNO such structure\n";
}

void doCommand(string& command, LinearList& lst, BinaryTree& tr){
    if (command == "--help") help();
    else if (command == "--list") list(lst);
    else if (command == "--lt") lt(lst, tr);
    else if (command == "--tree") tree(tr);
    else if (command == "--tl") tl(lst, tr);
    else if (command == "--pf") pf(tr);
    else if (command == "--show") show(lst, tr);
    else cout << "\nWRONG COMMAND\n";
}

int main(){
    LinearList lst = LinearList();
    BinaryTree tr = BinaryTree();
    help();
    string command;
    while (true){
        cin >> command;
        if (command == "--exit") {
            cout << "\nThe PROGRAM is exited\n";
            break;
        } else doCommand(command, lst, tr);
    }
    return 0;
}
