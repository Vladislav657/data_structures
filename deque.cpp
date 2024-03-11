#include <iostream>

using namespace std;
typedef int inf;


class Node{
public:
    inf data;
    Node *prev;
    Node *next;

    explicit Node(inf data){
        this->data = data;
        this->prev = this->next = nullptr;
    }
};


class Stack{
protected:
    Node *head;

public:
    Stack(){
        this->head = nullptr;
    }

    bool empty(){
        return head == nullptr;
    }

    Node *first(){
        return this->head;
    }

    virtual Node *popFront(){
        if (this->head == nullptr) return nullptr;
        Node *node = this->head;
        this->head = this->head->next;
        node->next = nullptr;
        return node;
    }

    virtual void pushFront(Node *node){
        node->next = this->head;
        this->head = node;
    }

    void print(){
        cout << "{";
        Node *node = this->head;
        while (node != nullptr){
            if (node != this->head) cout << ", ";
            cout << node->data;
            node = node->next;
        }
        cout << "}\n";
    }
};


class Queue: public Stack{
private:
    using Stack::head;
    using Stack::pushFront;

public:
    void pushBack(Node *node){
        Node *current = this->head;
        if (current == nullptr) {
            this->head = node;
            return;
        }
        while (current->next != nullptr) current = current->next;
        current->next = node;
    }
};


class Deque: public Stack{
private:
    using Stack::head;
    Node *tail;

public:
    Deque(){
        this->head = this->tail = nullptr;
    }

    Node *popFront() override{
        Node *node = this->head;
        if (this->head == nullptr) return node;
        if (this->head->next == nullptr){
            this->head = this->tail = nullptr;
            return node;
        }
        this->head = this->head->next;
        this->head->prev = nullptr;
        node->next = nullptr;
        return node;
    }

    Node *popBack(){
        Node *node = this->tail;
        if (this->tail == nullptr) return node;
        if (this->tail->prev == nullptr){
            this->head = this->tail = nullptr;
            return node;
        }
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
        node->prev = nullptr;
        return node;
    }

    void pushFront(Node *node) override{
        if (this->head == nullptr){
            this->head = this->tail = node;
            return;
        }
        this->head->prev = node;
        node->next = this->head;
        this->head = node;
    }

    void pushBack(Node *node){
        if (this->tail == nullptr){
            this->head = this->tail = node;
            return;
        }
        this->tail->next = node;
        node->prev = this->tail;
        this->tail = node;
    }

    Node *last(){
        return this->tail;
    }
};


void help(){
    cout << "\nYou have Stack, Queue and Deque; possible OPERATIONS:\n";
    cout << "\n--help (show all operations)";
    cout << "\n--empty 'flag' (is empty: 'Yes' or 'No'; flags: -s -q -d)";
    cout << "\n--pop_front 'flag' (pop first element; flags: -s -q -d)";
    cout << "\n--pop_back 'flag' (pop last element; flags: -d)";
    cout << "\n--push_front 'flag' 'elem' (push to start; flags: -s -d)";
    cout << "\n--push_back 'flag' 'elem' (push to end; flags: -q -d)";
    cout << "\n--first 'flag' (get first element; flags: -s -q -d)";
    cout << "\n--last 'flag' (get last element; flags: -d)";
    cout << "\n--show 'flag' (show structure; flags: -s -q -d)";
    cout << "\n--all (show all structures)";
    cout << "\n--exit (exit the program)\n\n";
}

void empty(Stack& stack, Queue& queue, Deque& deque){
    string flag;
    cin >> flag;
    if (flag == "-s") stack.empty() ? cout << "\nYes\n" : cout << "\nNo\n";
    else if (flag == "-q") queue.empty() ? cout << "\nYes\n" : cout << "\nNo\n";
    else if (flag == "-d") deque.empty() ? cout << "\nYes\n" : cout << "\nNo\n";
    else cout << "\nWrong flag\n";
}

void pop_front(Stack& stack, Queue& queue, Deque& deque){
    string flag;
    cin >> flag;
    if (flag == "-s"){
        Node *popped = stack.popFront();
        if (popped == nullptr){
            cout << "\nStack is empty\n";
            return;
        }
        cout << "\nYou popped element: " << popped->data << " from Stack:\n";
        stack.print();
        delete popped;
    }
    else if (flag == "-q"){
        Node *popped = queue.popFront();
        if (popped == nullptr){
            cout << "\nQueue is empty\n";
            return;
        }
        cout << "\nYou popped element: " << popped->data << " from Queue:\n";
        queue.print();
        delete popped;
    }
    else if (flag == "-d") {
        Node *popped = deque.popFront();
        if (popped == nullptr){
            cout << "\nDeque is empty\n";
            return;
        }
        cout << "\nYou popped element: " << popped->data << " from Deque:\n";
        deque.print();
        delete popped;
    }
    else cout << "\nWrong flag\n";
}

void pop_back(Deque& deque){
    string flag;
    cin >> flag;
    if (flag == "-d") {
        Node *popped = deque.popBack();
        if (popped == nullptr){
            cout << "\nDeque is empty\n";
            return;
        }
        cout << "\nYou popped element: " << popped->data << " from Deque:\n";
        deque.print();
        delete popped;
    }
    else cout << "\nWrong flag\n";
}

void push_front(Stack& stack, Deque& deque){
    string flag; int n;
    cin >> flag;
    if (scanf("%d", &n) != 1){
        cout << "\nWrong input\n";
        return;
    }
    if (flag == "-s"){
        Node *node = new Node(n);
        stack.pushFront(node);
        cout << "\nYou pushed element: " << node->data << " to Stack:\n";
        stack.print();
    }
    else if (flag == "-d") {
        Node *node = new Node(n);
        deque.pushFront(node);
        cout << "\nYou pushed element: " << node->data << " to Deque:\n";
        deque.print();
    }
    else cout << "\nWrong flag\n";
}

void push_back(Queue& queue, Deque& deque){
    string flag; int n;
    cin >> flag;
    if (scanf("%d", &n) != 1){
        cout << "\nWrong input\n";
        return;
    }
    if (flag == "-q"){
        Node *node = new Node(n);
        queue.pushBack(node);
        cout << "\nYou pushed element: " << node->data << " to Queue:\n";
        queue.print();
    }
    else if (flag == "-d") {
        Node *node = new Node(n);
        deque.pushBack(node);
        cout << "\nYou pushed element: " << node->data << " to Deque:\n";
        deque.print();
    }
    else cout << "\nWrong flag\n";
}

void first(Stack& stack, Queue& queue, Deque& deque){
    string flag;
    cin >> flag;
    if (flag == "-s"){
        Node *node = stack.first();
        if (node == nullptr){
            cout << "\nStack is empty\n";
            return;
        }
        cout << "\nFirst Stack element: " << node->data << "\nStack: ";
        stack.print();
    }
    else if (flag == "-q"){
        Node *node = queue.first();
        if (node == nullptr){
            cout << "\nQueue is empty\n";
            return;
        }
        cout << "\nFirst Queue element: " << node->data << "\nQueue: ";
        queue.print();
    }
    else if (flag == "-d"){
        Node *node = deque.first();
        if (node == nullptr){
            cout << "\nDeque is empty\n";
            return;
        }
        cout << "\nFirst Deque element: " << node->data << "\nDeque: ";
        deque.print();
    }
    else cout << "\nWrong flag\n";
}

void last(Deque& deque){
    string flag;
    cin >> flag;
    if (flag == "-d"){
        Node *node = deque.last();
        if (node == nullptr){
            cout << "\nDeque is empty\n";
            return;
        }
        cout << "\nLast Deque element: " << node->data << "\nDeque: ";
        deque.print();
    }
    else cout << "\nWrong flag\n";
}

void show(Stack& stack, Queue& queue, Deque& deque){
    string flag;
    cin >> flag;
    if (flag == "-s"){
        cout << "\nStack: ";
        stack.print();
    }
    else if (flag == "-q"){
        cout << "\nQueue: ";
        queue.print();
    }
    else if (flag == "-d"){
        cout << "\nDeque: ";
        deque.print();
    }
    else cout << "\nWrong flag\n";
}

void all(Stack& stack, Queue& queue, Deque& deque){
    cout << "\nStack: ";
    stack.print();
    cout << "\nQueue: ";
    queue.print();
    cout << "\nDeque: ";
    deque.print();
}

void operate(string& command, Stack& stack, Queue& queue, Deque& deque){
    if (command == "--help") help();
    else if (command == "--empty") empty(stack, queue, deque);
    else if (command == "--pop_front") pop_front(stack, queue, deque);
    else if (command == "--pop_back") pop_back(deque);
    else if (command == "--push_front") push_front(stack, deque);
    else if (command == "--push_back") push_back(queue, deque);
    else if (command == "--first") first(stack, queue, deque);
    else if (command == "--last") last(deque);
    else if (command == "--show") show(stack, queue, deque);
    else if (command == "--all") all(stack, queue, deque);
    else cout << "\nWrong command\n";
}


int main(){
    Stack stack; Queue queue; Deque deque;
    help();
    string command;
    while (true){
        cin >> command;
        if (command == "--exit"){
            cout << "\nThe program is exited";
            break;
        } else operate(command, stack, queue, deque);
    }
    return 0;
}
