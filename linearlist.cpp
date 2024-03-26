#include <iostream>
#include <map>

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
    Node *head;

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

    static double operate(double a, double b, char op){
        switch (op) {
            case '*':
                return a * b;
            case '/':
                return a / b;
            case '+':
                return a + b;
            case '-':
                return a - b;
            default:
                return 0;
        }
    }

    static double calc(LinearList *exp, map<char, double>&identifiers){
        if (exp->empty()) return 0;
        if (exp->atomic()) return identifiers[exp->head->atom];
        double res = calc(exp->header(), identifiers);
        while (!exp->empty()){
            char op = exp->header()->head->atom;
            double x = calc(exp->header(), identifiers);
            res = operate(res, x, op);
        }
        return res;
    }

public:
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
        char first = list.pop()->data;
        this->head = first == '(' ? new Node() : new Node(first);
        push(list, this->head);
    }

    bool empty(){
        return this->head->tag == 0 && this->head->next == nullptr && head->level == nullptr;
    }

    bool atomic(){
        return this->head->tag == 1 && this->head->next == nullptr;
    }

    Node *divide(){
        if (this->empty() || this->atomic()) return nullptr;
        Node *node = this->head->level;
        node->next = nullptr;
        return node;
    }

    LinearList *header(){
        if (this->empty() || this->atomic()) return nullptr;
        Node *node = head->level;
        head->level = head->level->next;
        node->next = nullptr;
        auto *lst = new LinearList(node);
        return lst;
    }

    double calculate(map<char, double>&identifiers){
        return calc(this, identifiers);
    }

    void print(){
        show(this->head);
        cout << endl;
    }
};


bool isRight(string& exp, map<char, double>& identifiers) {
    if (exp[0] != '(' || exp[exp.size() - 1] != ')') return false;
    Stack balance = Stack();
    for (char i : exp) {
        if (i == '(') balance.push(new Char(i));
        else if (i == ')') if (balance.pop() == nullptr) return false;
    }
    if (!balance.empty()) return false;
    int index = 0;
    for (int i = 1; i < exp.size() - 1; ++i) {
        if (exp[i] == '*' || exp[i] == '/' || exp[i] == '+' || exp[i] == '-') {
            if (index % 2 == 0 || exp[i - 1] == '(' || exp[i + 1] == ')' || exp[i] == '/' &&
            identifiers[exp[i + 1]] == 0) return false;
            index++;
        } else if (exp[i] >= 'a' && exp[i] <= 'z'){
            if (index % 2 == 1 || exp[i - 1] == ')' || exp[i + 1] == '(') return false;
            index++;
        } else if (exp[i] == '(' || exp[i] == ')') continue;
        else return false;
    }
    return true;
}


void help(){
    cout << "You can enter ARITHMETIC EXPRESSION and get ANSWER, commands:\n\n";
    cout << "--help (show ALL COMMANDS)\n";
    cout << "--exp (enter EXPRESSION and then CALCULATE)\n";
    cout << "--init 'name' 'value' (initialise ONE LETTER IDENTIFIER: 'a-z', default '0', example: '--init a 867')\n";
    cout << "--show 'name' (show IDENTIFIER with name 'name')\n";
    cout << "--all (show ALL IDENTIFIERS)\n";
    cout << "--exit (exit the PROGRAM)\n\n";
}

void exp(map<char, double>& identifiers){
    string expression;
    cout << "\nENTER ARITHMETIC EXPRESSION (NO space, use ONE LETTER IDENTIFIERS, example: '((a+b)*(c-d))'):\n";
    cin >> expression;
    if (!isRight(expression, identifiers)){
        cout << "\nWRONG expression\n";
        return;
    }
    Stack expStack = Stack();
    for (int i = (int)expression.size() - 1; i >= 0; --i) expStack.push(new Char(expression[i]));
    auto exp = LinearList(expStack);
    cout << "\nResult: " << exp.calculate(identifiers) << endl;
}

void init(map<char, double>& identifiers){
    char identifier;
    double value;
    cin >> identifier;
    if (identifier < 'a' || identifier > 'z'){
        cout << "\nWRONG identifier, use LETTERS: 'a-z'\n";
        return;
    }
    if (scanf("%lf", &value) != 1){
        cout << "\nWRONG value, use NUMBERS\n";
        return;
    }
    identifiers[identifier] = value;
    cout << "\nYou initialized identifier '" << identifier << "' with value '" << value << "'\n";
}

void show(map<char, double>& identifiers){
    char identifier;
    cin >> identifier;
    if (identifier < 'a' || identifier > 'z'){
        cout << "\nNO such identifier, use LETTERS: 'a-z'\n";
        return;
    }
    cout << "\n" << identifier << " = " << identifiers[identifier] << "\n";
}

void all(map<char, double>& identifiers){
    cout << "\n";
    for (char i = 'a'; i <= 'z'; ++i) {
        cout << i << " = " << identifiers[i];
        if (i != 'z') cout << "; ";
    }
    cout << "\n";
}

void doCommand(string& command, map<char, double>& identifiers){
    if (command == "--help") help();
    else if (command == "--exp") exp(identifiers);
    else if (command == "--init") init(identifiers);
    else if (command == "--show") show(identifiers);
    else if (command == "--all") all(identifiers);
    else cout << "\nWRONG COMMAND\n";
}

int main(){
    map<char, double>identifiers;
    help();
    string command;
    while (true){
        cin >> command;
        if (command == "--exit"){
            cout << "\nThe PROGRAM is exited\n";
            break;
        } else doCommand(command, identifiers);
    }
    return 0;
}
