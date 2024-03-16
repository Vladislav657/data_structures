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

    bool empty(){
        return this->head == nullptr;
    }

    Sign *first(){
        return this->head;
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

    bool empty(){
        return this->head == nullptr;
    }

    Operand *first(){
        return this->head;
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
            return a / b;
        case '+':
            return a + b;
        case '-':
            return a - b;
        default:
            return 0;
    }
}

double calculate(string& exp, map<char, double>& identifiers){
    double res = 0;
    OperandStack operands = OperandStack();
    for (char i : exp) {
        if (i >= 'a' && i <= 'z') operands.push(new Operand(identifiers[i]));
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
            if (exp[i - 1] != '*' && exp[i - 1] != '/' && exp[i - 1] != '+' && exp[i - 1] != '-') return false;
            if (exp[i + 1] < 'a' || exp[i + 1] > 'z') return false;
            balance++;
        } else if (exp[i] == ')') {
            if (i == 0) return false;
            if (i == exp.size() - 1) {
                if (balance > 0) balance--;
                continue;
            }
            if (exp[i + 1] != '*' && exp[i + 1] != '/' && exp[i + 1] != '+' && exp[i + 1] != '-') return false;
            if (exp[i - 1] < 'a' || exp[i - 1] > 'z') return false;
            if (balance > 0) balance--;
        } else if (exp[i] >= 'a' && exp[i] <= 'z') {
            if (index % 2 == 1) return false;
            index++;
        }
    }
    if (balance != 0) return false;
    return true;
}

string strip(string& exp){
    string result;
    for (char i : exp) if (i != ' ') result.push_back(i);
    return result;
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
    while (!signs.empty()) result.push_back(signs.pop()->data);
    return result;
}

void help(){
    cout << "You can enter ARITHMETIC EXPRESSION and get ANSWER, commands:\n";
    cout << "--exp (enter EXPRESSION and then CALCULATE)\n";
    cout << "--init 'name' 'value' (initialise ONE LETTER IDENTIFIER, example: '--init a 867')\n";
    cout << "--show 'name' (show IDENTIFIER with name 'name')\n";
    cout << "--all (show ALL IDENTIFIERS)\n";
    cout << "--exit (exit the PROGRAM)\n\n";
}

int main(){
    map<char, double>identifiers;
    identifiers['d'] = 90;

    string s;
//    cin >> s;
    s = setParentheses(s);
//    string postfix = toPostfix(s);
//    cout << s;
    return 0;
}
