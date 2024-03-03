#include <iostream>
#include <vector>

using namespace std;


class Node{ // елемент строки (символ)
public:
    char data;
    Node *prev;
    Node *next;

    Node(char data = '\0'){
        this->data = data;
        prev = next = nullptr;
    }
};


class String{ // строка
private:
    Node *head;
    Node *tail;
    int length;

public:
    String(){ // создать
        head = tail = nullptr;
        length = 0;
    }

    void pushFront(char ch){ // добавить символ с начала
        Node *node = new Node(ch);
        if (length == 0){
            head = tail = node;
            length++;
            return;
        }
        head->prev = node;
        node->next = head;
        head = node;
        length++;
    }

    void pushBack(char ch){ // добавить символ с конца
        Node *node = new Node(ch);
        if (length == 0){
            tail = head = node;
            length++;
            return;
        }
        tail->next = node;
        node->prev = tail;
        tail = node;
        length++;
    }

    void insert(char ch, int index){ // добавить символ по индексу
        if (index < 0 || index > length) return;
        if (index == 0){
            pushFront(ch);
            return;
        }
        if (index == length){
            pushBack(ch);
            return;
        }
        Node *node = new Node(ch);
        Node *current = head;
        for (int i = 1; i < length; ++i) {
            current = current->next;
            if (i == index) break;
        }
        current->prev->next = node;
        node->prev = current->prev;
        current->prev = node;
        node->next = current;
        length++;
    }

    Node *popFront(){ // удалить символ с начала
        Node *node = head;
        if (length == 0) return node;
        if (length == 1){
            head = tail = nullptr;
            length--;
            return node;
        }
        head = head->next;
        head->prev = nullptr;
        node->next = nullptr;
        length--;
        return node;
    }

    Node *popBack(){ // удалить символ с конца
        Node *node = tail;
        if (length == 0) return node;
        if (length == 1){
            tail = head = nullptr;
            length--;
            return node;
        }
        tail = tail->prev;
        tail->next = nullptr;
        node->prev = nullptr;
        length--;
        return node;
    }

    Node *remove(int index){ // удалить символ по индексу
        Node *node = nullptr;
        if (index < 0 || index >= length) return node;
        if (index == 0) return popFront();
        if (index == length - 1) return popBack();
        node = head;
        for (int i = 1; i < length - 1; ++i) {
            node = node->next;
            if (i == index) break;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = node->prev = nullptr;
        length--;
        return node;
    }

    Node *get(int index) const{ // получить символ по индексу
        Node *node = nullptr;
        if (index < 0 || index >= length) return node;
        node = head;
        for (int i = 0; i < length; ++i) {
            if (i == index) break;
            node = node->next;
        }
        return node;
    }

    bool isEmpty() const{ // пустая ли строка
        return length == 0;
    }

    bool contains(string& s) const{ // содержит ли строка подстроку
        if (s.length() > length || s.empty()) return false;
        bool flag = false;
        Node *start = head;
        Node *current;
        for (int i = 0; i < length - s.length() + 1; ++i) {
            flag = true;
            current = start;
            for (int j = 0; j < s.length(); ++j) {
                if (current->data != s[j]) {
                    flag = false;
                    break;
                }
                current = current->next;
            }
            if (flag) return flag;
            start = start->next;
        }
        return flag;
    }

    String *slice(int start, int end) const{ // срез строки
        if (start < 0 || start >= length || end < 0 || end >= length || end <= start) return nullptr;
        auto *slice = new String();
        Node *node = get(start);
        for (int i = start; i <= end; ++i) {
            slice->pushBack(node->data);
            node = node->next;
        }
        return slice;
    }

    String operator + (String& other) const{ // конкатенация строк
        String res = String();
        Node *node = this->head;
        for (int i = 0; i < this->len(); ++i){
            res.pushBack(node->data);
            node = node->next;
        }
        node = other.head;
        for (int i = 0; i < other.len(); ++i){
            res.pushBack(node->data);
            node = node->next;
        }
        return res;
    }

    void operator += (string& other){ // расширение строки
        for (int i = 0; i < other.length(); ++i) this->pushBack(other[i]);
    }

    int len() const{ // длина строки
        return length;
    }

    void print(){ // вывести строку
        Node *node = head;
        for (int i = 0; i < length; ++i){
            cout << node->data;
            node = node->next;
        }
        cout << endl;
    }
};


// функции пользовательского интерфейса
void help(){
    cout << "Possible OPERATIONS:";
    cout << "\n--help (show ALL OPERATIONS)";
    cout << "\n--insert 'num' 'char' 'index' (insert to STRING with number 'num' char 'char' to index 'index')";
    cout << "\n--remove 'num' 'index' (remove from STRING with number 'num' char with index 'index')";
    cout << "\n--get 'num' 'index' (get from STRING with number 'num' char with index 'index')";
    cout << "\n--empty 'num' (prints 'yes' if STRING with number 'num' is empty else 'no')";
    cout << "\n--contains 'num' 'str' ('yes' if STRING with number 'num' contains STRING 'str' else 'no')";
    cout << "\n--slice 'num' 'start' 'end' (slice of STRING with number 'num' from 'start' to 'end')";
    cout << "\n--concat 'num1' 'num2' (concatenate STRING with numbers 'num1' and 'num2')";
    cout << "\n--extend 'num' 'str' (extend STRING with number 'num' with string 'str')";
    cout << "\n--len 'num' (length of STRING with number 'num')";
    cout << "\n--show 'num' (show STRING with number 'num')";
    cout << "\n--all (show ALL STRINGS)";
    cout << "\n--exit (exit the PROGRAM)\n\n";
}

void insert(vector<String>&strings){
    int number, index;
    char ch;
    if (scanf("%d %c %d", &number, &ch, &index) == 3 && number >= 0 && number < strings.size()){
        int prevLen = strings[number].len();
        strings[number].insert(ch, index);
        int nextLen = strings[number].len();
        if (nextLen - prevLen == 0){
            cout << "\nIncorrect index\n";
            return;
        }
        cout << "\nYou inserted char " << ch << " to string with number " << number << " to index " << index;
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
    } else cout << "\nWRONG input or incorrect string number\n";
}

void remove(vector<String>&strings){
    int number, index;
    if (scanf("%d %d", &number, &index) == 2 && number >= 0 && number < strings.size()){
        Node *deleted = strings[number].remove(index);
        if (deleted == nullptr){
            cout << "\nIncorrect index\n";
            return;
        }
        cout << "\nYou removed char " << deleted->data << " with index " << index << " from string with number " << number;
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
        delete deleted;
    } else cout << "\nWRONG input or incorrect string number\n";
}

void get(vector<String>&strings){
    int number, index;
    if (scanf("%d %d", &number, &index) == 2 && number >= 0 && number < strings.size()){
        Node *got = strings[number].get(index);
        if (got == nullptr){
            cout << "\nIncorrect index\n";
            return;
        }
        cout << "\nCurrent char: " << got->data << "; index " << index;
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
        delete got;
    } else cout << "\nWRONG input or incorrect string number\n";
}

void empty(vector<String>&strings){
    int number;
    if (scanf("%d", &number) == 1 && number >= 0 && number < strings.size()){
        strings[number].isEmpty() ? cout << "\nYes\n" : cout << "\nNo\n";
    } else cout << "\nWRONG input or incorrect string number\n";
}

void contains(vector<String>&strings){
    int number;
    string str;
    if (scanf("%d ", &number) == 1 && number >= 0 && number < strings.size()){
        cin >> str;
        strings[number].contains(str) ? cout << "\nYes\n" : cout << "\nNo\n";
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
    } else cout << "\nWRONG input or incorrect string number\n";
}

void slice(vector<String>&strings){
    int number, start, end;
    if (scanf("%d %d %d", &number, &start, &end) == 3 && number >= 0 && number < strings.size()){
        String *slice = strings[number].slice(start, end);
        if (slice == nullptr){
            cout << "\nIncorrect start and end indices\n";
            return;
        }
        cout << endl;
        slice->print();
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
        delete slice;
    } else cout << "\nWRONG input or incorrect string number\n";
}

void concat(vector<String>&strings){
    int number1, number2;
    if (scanf("%d %d", &number1, &number2) == 2 && number1 >= 0 && number1 < strings.size() &&
    number2 >= 0 && number2 < strings.size()){
        String res = strings[number1] + strings[number2];
        cout << endl;
        res.print();
        cout << "\nSTRING " << number1 << ": ";
        strings[number1].print();
        cout << "\nSTRING " << number2 << ": ";
        strings[number2].print();
    } else cout << "\nWRONG input or incorrect string numbers\n";
}

void extend(vector<String>&strings){
    int number;
    string str;
    if (scanf("%d ", &number) == 1 && number >= 0 && number < strings.size()){
        cin >> str;
        strings[number] += str;
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
    } else cout << "\nWRONG input or incorrect string number\n";
}

void len(vector<String>&strings){
    int number;
    if (scanf("%d", &number) == 1 && number >= 0 && number < strings.size()){
        cout << "\n" << strings[number].len() << "\n";
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
    } else cout << "\nWRONG input or incorrect string number\n";
}

void show(vector<String>&strings){
    int number;
    if (scanf("%d", &number) == 1 && number >= 0 && number < strings.size()){
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
    } else cout << "\nWRONG input or incorrect string number\n";
}

void all(vector<String>&strings){
    for (int i = 0; i < strings.size(); ++i) {
        cout << "\nSTRING " << i << ": ";
        strings[i].print();
    }
    cout << endl;
}

void operate(const string& command, vector<String>&strings){
    if (command == "--help") help();
    else if (command == "--insert") insert(strings);
    else if (command == "--remove") remove(strings);
    else if (command == "--get") get(strings);
    else if (command == "--empty") empty(strings);
    else if (command == "--contains") contains(strings);
    else if (command == "--slice") slice(strings);
    else if (command == "--concat") concat(strings);
    else if (command == "--extend") extend(strings);
    else if (command == "--len") len(strings);
    else if (command == "--show") show(strings);
    else if (command == "--all") all(strings);
    else cout <<  "\nWRONG input\n";
}


int main(){
    int count;
    cout << "STRING is a structure of CHARS\nENTER a count of STRINGS to create:\n";
    cin >> count;
    if (!cin){
        cout << "\nIncorrect input (expected number)\n";
        return 0;
    }
    vector<String>strings(count);
    for (int i = 0; i < count; ++i) strings[i] = String();
    cout << "You created " << count << " STRINGS; STRING numbers: ";
    for (int i = 0; i < count; ++i) cout << i << " ";
    cout << endl;
    help();
    string command;
    while (true){
        cin >> command;
        if (command == "--exit"){
            cout << "\nThe PROGRAM exited";
            break;
        }
        else operate(command, strings);
    }
    return 0;
}
