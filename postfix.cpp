#include <iostream>
#include <map>

using namespace std;

class Sign{
public:
    char data;
    Sign *next;

    explicit Sign(char data){
        this->data = data;
        this->next = nullptr;
    }
};

class Operand{
public:
    double data;
    Operand *next;

    explicit Operand(double data){
        this->data = data;
        this->next = nullptr;
    }
};

class SignStack{
private:
    Sign *head;

public:
    SignStack(){
        this->head = nullptr;
    }

    void push(Sign *sign){
        sign->next = this->head;
        this->head = sign;
    }

    Sign *pop(){
        Sign *sign = this->head;
        if (sign != nullptr){
            this->head = this->head->next;
            sign->next = nullptr;
        }
        return sign;
    }
};

class OperandStack{
private:
    Operand *head;

public:
    OperandStack(){
        this->head = nullptr;
    }

    void push(Operand *operand){
        operand->next = this->head;
        this->head = operand;
    }

    Operand *pop(){
        Operand *operand = this->head;
        if (operand != nullptr){
            this->head = this->head->next;
            operand->next = nullptr;
        }
        return operand;
    }
};

double operate(double a, double b, char op){
    switch (op) {
        case '*':
            return a * b;
        case '/':
            return b == 0 ? 0 : a / b;
        case '+':
            return a + b;
        case '-':
            return a - b;
        default:
            return 0;
    }
}

double calculate(string& exp, map<char, double>& identifiers){
    OperandStack operands = OperandStack();
    for (char i : exp) {
        if (i >= 'a' && i <= 'z'){
            operands.push(new Operand(identifiers[i]));
            continue;
        }
        double b = operands.pop()->data;
        double a = operands.pop()->data;
        operands.push(new Operand(operate(a, b, i)));
    }
    return operands.pop()->data;
}

bool isRight(string& exp) {
    int balance = 0, index = 0;
    for (int i = 0; i < exp.size(); ++i) {
        if (exp[i] == '*' || exp[i] == '/' || exp[i] == '+' || exp[i] == '-') {
            if (index % 2 == 0) return false;
            index++;
        } else if (exp[i] == '(') {
            if (i == 0) {
                balance++;
                continue;
            }
            if (i == exp.size() - 1) return false;
            if (exp[i + 1] == '*' || exp[i + 1] == '/' || exp[i + 1] == '+' || exp[i + 1] == '-') return false;
            if (exp[i - 1] >= 'a' && exp[i - 1] <= 'z') return false;
            balance++;
        } else if (exp[i] == ')') {
            if (i == 0) return false;
            if (i == exp.size() - 1) {
                if (balance > 0) balance--;
                continue;
            }
            if (exp[i - 1] == '*' || exp[i - 1] == '/' || exp[i - 1] == '+' || exp[i - 1] == '-') return false;
            if (exp[i + 1] >= 'a' && exp[i + 1] <= 'z') return false;
            if (balance > 0) balance--;
        } else if (exp[i] >= 'a' && exp[i] <= 'z') {
            if (index % 2 == 1) return false;
            index++;
        }
    }
    if (balance != 0 || index == 0) return false;
    return true;
}

string setParentheses(string& exp){
    string result = "(";
    for (int i = 0; i < exp.size(); ++i) {
        if (i < exp.size() - 2 && (exp[i + 1] == '*' || exp[i + 1] == '/') && exp[i] >= 'a' && exp[i] <= 'z'
        && exp[i + 2] >= 'a' && exp[i + 2] <= 'z')
            result.push_back('(');
        result.push_back(exp[i]);
        if (i > 1 && (exp[i - 1] == '*' || exp[i - 1] == '/') && exp[i] >= 'a' && exp[i] <= 'z'
        && exp[i - 2] >= 'a' && exp[i - 2] <= 'z')
            result.push_back(')');
    }
    result.push_back(')');
    return result;
}

string toPostfix(string& right){
    SignStack signs = SignStack();
    string result;
    for (char i : right) {
        if (i == ')'){
            char sign = signs.pop()->data;
            while (sign != '('){
                result.push_back(sign);
                sign = signs.pop()->data;
            }
        }
        else if (i >= 'a' && i <= 'z'){
            result.push_back(i);
        }
        else{
            signs.push(new Sign(i));
        }
    }
    return result;
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
    cout << "\nENTER ARITHMETIC EXPRESSION (NO space, use ONE LETTER IDENTIFIERS, example: '(a+b)*(c-d)'):\n";
    cin >> expression;
    if (!isRight(expression)){
        cout << "\nWRONG expression\n";
        return;
    }
    expression = setParentheses(expression);
    string postfix = toPostfix(expression);
    cout << "\nResult: " << calculate(postfix, identifiers) << endl;
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
