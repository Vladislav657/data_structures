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
    String(){
        head = tail = nullptr;
        length = 0;
    }

    String(string& start_str){ // создать с начальной строкой
        head = tail = nullptr;
        length = 0;
        for (int i = 0; i < start_str.length(); ++i) this->push(start_str[i]);
    }

    void push(char ch){ // добавить символ в конец
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

    void insert(int index, String &str){ // вставить строку по индексу
        if (index < 0 || index > length || str.head == nullptr) return;
        if (this->head == nullptr){
            this->head = str.head;
            this->tail = str.tail;
        } else if (index == 0){
            str.tail->next = this->head;
            this->head->prev = str.tail;
            this->head = str.head;
        } else if (index == length){
            str.head->prev = this->tail;
            this->tail->next = str.head;
            this->tail = str.tail;
        } else {
            Node *node = get(index);
            node->prev->next = str.head;
            str.head->prev = node->prev;
            node->prev = str.tail;
            str.tail->next = node;
        }
        this->length += str.length;
    }

    String *remove(int start, int end){ // вырезать подстроку по индексам start и end
        if (start < 0 || start >= length || end < 0 || end >= length || start > end) return nullptr;
        auto *removed = new String();
        Node *left = get(start);
        Node *right = get(end);
        if (start == 0) this->head = right->next;
        if (end == length - 1) this->tail = left->prev;
        if (left->prev != nullptr) left->prev->next = right->next;
        if (right->next != nullptr) right->next->prev = left->prev;
        left->prev = right->next = nullptr;
        removed->head = left;
        removed->tail = right;
        removed->length = end - start + 1;
        this->length -= removed->length;
        return removed;
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

    int find(String& s) const{ // поиск подстроки
        if (s.len() > length || s.len() == 0) return -1;
        bool flag;
        Node *start = this->head;
        Node *current, *other;
        for (int i = 0; i < length - s.len() + 1; ++i) { // helloWorld
            flag = true;
            current = start;
            other = s.head;
            for (int j = 0; j < s.len(); ++j) {
                if (current->data != other->data) {
                    flag = false;
                    break;
                }
                current = current->next;
                other = other->next;
            }
            if (flag) return i;
            start = start->next;
        }
        return -1;
    }

    void replace(String& sub_old, String& sub_new){
        int start = this->find(sub_old);
        if (start == -1) return;
        int end = start + sub_old.len() - 1;
        this->remove(start, end);
        this->insert(start, sub_new);
    }

    String *divide(int index){ // разделение строки
        if (index < 0 || index >= length) return nullptr;
        auto *slice = new String();
        Node *node = get(index);
        slice->head = node;
        slice->tail = this->tail;
        this->tail = node->prev;
        if (index == 0) this->head = node->prev;
        if (this->tail != nullptr) this->tail->next = nullptr; // 0 1 2 3 4 5 6 7
        slice->head->prev = nullptr;
        slice->length = this->length - index;
        this->length -= slice->length;
        return slice;
    }

    String *operator + (String& other) const{ // конкатенация строк
        String *left = this->copy();
        String *right = other.copy();
        auto *res = new String();
        if (left->tail != nullptr && right->head != nullptr){
            left->tail->next = right->head;
            res->head = left->head;
            res->tail = right->tail;
        } else if (left->tail != nullptr) res = left;
        else res = right;
        res->length = left->length + right->length;
        return res;
    }

    void operator += (String& other){ // конкатенация строк с изменением
        String *right = other.copy();
        if (this->tail != nullptr && right->head != nullptr){
            this->tail->next = right->head;
            this->tail = right->tail;
        } else if (right->tail != nullptr){
            this->head = right->head;
            this->tail = right->tail;
        }
        this->length += right->length;
    }

    String *copy() const{ // копия строки
        auto *copy = new String();
        Node *node = head;
        for (int i = 0; i < length; ++i) {
            copy->push(node->data);
            node = node->next;
        }
        return copy;
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
    cout << "\n--push 'num' 'char' (push to STRING with number 'num' char 'char' at the end)";
    cout << "\n--insert 'num' 'index' 'str'(insert to STRING with number 'num' to index 'index' string 'str')";
    cout << "\n--remove 'num' 'start' 'end' (remove from STRING with number 'num' substring by indices)";
    cout << "\n--get 'num' 'index' (get from STRING with number 'num' char with index 'index')";
    cout << "\n--find 'num' 'str' (find in STRING with number 'num' STRING 'str' and print index of first char)";
    cout << "\n--divide 'num' 'index' (divide STRING with number 'num' by index 'index')";
    cout << "\n--concat 'num1' 'num2' (concatenate STRINGS with numbers 'num1' and 'num2')";
    cout << "\n--extend 'num1' 'num2' (extend STRING with number 'num1' by string with number 'num2')";
    cout << "\n--replace 'num' 'old' 'new' (replace STRING with number 'num' substring 'old' to substring 'new')";
    cout << "\n--len 'num' (length of STRING with number 'num')";
    cout << "\n--show 'num' (show STRING with number 'num')";
    cout << "\n--all (show ALL STRINGS)";
    cout << "\n--exit (exit the PROGRAM)\n\n";
}

void push(vector<String>&strings){
    int number;
    char ch;
    if (scanf("%d %c", &number, &ch) == 2 && number >= 0 && number < strings.size()){
        strings[number].push(ch);
        cout << "\nYou pushed char '" << ch << "'";
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
    } else cout << "\nWRONG input or incorrect string number\n";
}

void insert(vector<String>&strings){
    int number, index;
    string str;
    if (scanf("%d%d", &number, &index) == 2 && number >= 0 && number < strings.size()){
        cin >> str;
        auto s = String(str);
        int prevLen = strings[number].len();
        strings[number].insert(index, s);
        int nextLen = strings[number].len();
        if (nextLen - prevLen == 0){
            cout << "\nIncorrect index\n";
            return;
        }
        cout << "\nYou inserted string: " << str << "\nto string with number " << number << " to index " << index;
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
    } else cout << "\nWRONG input or incorrect string number\n";
}

void remove(vector<String>&strings){
    int number, start, end;
    if (scanf("%d%d%d", &number, &start, &end) == 3 && number >= 0 && number < strings.size()){
        String *deleted = strings[number].remove(start, end);
        if (deleted == nullptr){
            cout << "\nIncorrect indices\n";
            return;
        }
        cout << "\nYou removed substring: ";
        deleted->print();
        cout << "from string with number " << number;
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
        delete deleted;
    } else cout << "\nWRONG input or incorrect string number\n";
}

void get(vector<String>&strings){
    int number, index;
    if (scanf("%d%d", &number, &index) == 2 && number >= 0 && number < strings.size()){
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

void find(vector<String>&strings){
    int number;
    string str;
    if (scanf("%d ", &number) == 1 && number >= 0 && number < strings.size()){
        cin >> str;
        auto s = String(str);
        int index = strings[number].find(s);
        if (index == -1){
            cout << "\nNo such substring\n";
            return;
        }
        cout << "\nIndex of first char: " << index;
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
    } else cout << "\nWRONG input or incorrect string number\n";
}

void divide(vector<String>&strings){
    int number, index;
    if (scanf("%d%d", &number, &index) == 2 && number >= 0 && number < strings.size()){
        String *slice = strings[number].divide(index);
        if (slice == nullptr){
            cout << "\nIncorrect index\n";
            return;
        }
        cout << "\nDivided part: ";
        slice->print();
        cout << "\nSTRING " << number << ": ";
        strings[number].print();
        delete slice;
    } else cout << "\nWRONG input or incorrect string number\n";
}

void concat(vector<String>&strings){
    int number1, number2;
    if (scanf("%d%d", &number1, &number2) == 2 && number1 >= 0 && number1 < strings.size() &&
    number2 >= 0 && number2 < strings.size()){
        String *res = strings[number1] + strings[number2];
        cout << endl;
        res->print();
        cout << "\nSTRING " << number1 << ": ";
        strings[number1].print();
        cout << "\nSTRING " << number2 << ": ";
        strings[number2].print();
    } else cout << "\nWRONG input or incorrect string numbers\n";
}

void extend(vector<String>&strings){
    int number1, number2;
    if (scanf("%d%d", &number1, &number2) == 2 && number1 >= 0 && number1 < strings.size() &&
        number2 >= 0 && number2 < strings.size()){
        strings[number1] += strings[number2];
        cout << "\nSTRING " << number1 << ": ";
        strings[number1].print();
        cout << "\nSTRING " << number2 << ": ";
        strings[number2].print();
    } else cout << "\nWRONG input or incorrect string numbers\n";
}

void replace(vector<String>&strings){
    int number;
    string str_old, str_new;
    if (scanf("%d ", &number) == 1 && number >= 0 && number < strings.size()){
        cin >> str_old >> str_new;
        auto o = String(str_old);
        auto n = String(str_new);
        strings[number].replace(o, n);
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
    else if (command == "--push") push(strings);
    else if (command == "--insert") insert(strings);
    else if (command == "--remove") remove(strings);
    else if (command == "--get") get(strings);
    else if (command == "--find") find(strings);
    else if (command == "--divide") divide(strings);
    else if (command == "--concat") concat(strings);
    else if (command == "--extend") extend(strings);
    else if (command == "--replace") replace(strings);
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
