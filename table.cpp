#include <iostream>
#include <utility>

using namespace std;
typedef string key_t;
typedef int value_t;

class Node{
public:
    key_t key;
    value_t value;
    Node *next;

    Node(key_t key, value_t value){
        this->key = std::move(key);
        this->value = value;
        this->next = nullptr;
    }

    void show() const{
        cout << this->key << ": " << this->value;
    }
};


class Table{
private:
    Node *head;

public:
    Table(){
        this->head = nullptr;
    }

    void insert(key_t key, value_t value){
        Node *node = new Node(std::move(key), value);
        if (head == nullptr){
            head = node;
            return;
        }
        if (node->key < head->key){
            node->next = head;
            head = node;
            return;
        }
        Node *current = head;
        while (current->next != nullptr && node->key >= current->next->key)
            current = current->next;
        if (current->key == node->key) current->value = node->value;
        else{
            node->next = current->next;
            current->next = node;
        }
    }

    Node *get(const key_t& key){
        Node *current = head;
        while (current != nullptr){
            if (current->key == key) return current;
            current = current->next;
        }
        return nullptr;
    }

    Node *remove(const key_t& key){
        Node *deleted = nullptr;
        if (head == nullptr) return deleted;
        if (head->next == nullptr){
            if (head->key == key){
                deleted = head;
                head = nullptr;
                return deleted;
            }
        }
        Node *prev = nullptr;
        Node *current = head;
        while (current != nullptr){
            if (current->key == key){
                deleted = current;
                if (current == head){
                    head = head->next;
                } else if (prev != nullptr){
                    prev->next = current->next;
                }
                return deleted;
            }
            prev = current;
            current = current->next;
        }
        return deleted;
    }

    bool clear(){
        return head == nullptr;
    }

    void show(){
        Node *current = head;
        cout << "\n{";
        while (current != nullptr){
            current->show();
            if (current->next != nullptr) cout << ", ";
            current = current->next;
        }
        cout << "}\n";
    }
};


void help(){
    cout << "\nTABLE is a structure of KEY-VALUE elements;\nYou can create 1(!) TABLE\nOPERATIONS:\n\n";
    cout << "--help (shows OPERATIONS)\n";
    cout << "--create (creates structure TABLE)\n";
    cout << "--add 'key' 'value' (adds element with key = 'key' and value = 'value' in TABLE)\n";
    cout << "--get 'key' (gets element with key = 'key')\n";
    cout << "--del 'key' (deletes element with key = 'key')\n";
    cout << "--clear (checks if TABLE is clear or NOT)\n";
    cout << "--show (shows TABLE)\n";
    cout << "--exit (exits the PROGRAM)\n\n";
}


int main(){
    Table table;
    bool created = false;
    string operation;
    help();
    while (true){
        cin >> operation;
        if (operation == "--help"){
            help();
        } else if (operation == "--create"){
            if (created){
                cout << "\nTABLE already CREATED\n";
                continue;
            }
            table = Table();
            created = true;
            cout << "\nYou created structure TABLE\n";
        } else if (operation == "--add"){
            if (!created){
                cout << "\nTABLE is NOT created\n";
                continue;
            }
            key_t key;
            value_t value;
            cin >> key;
            int c = scanf("%d", &value);
            if (c == 1){
                table.insert(key, value);
                cout << "\nYou added element with key = " << key << " and value = " << value;
                cout << "\nYour TABLE:";
                table.show();
            } else cout << "\nWRONG operation\n";
        } else if (operation == "--get"){
            if (!created){
                cout << "\nTABLE is NOT created\n";
                continue;
            }
            key_t key;
            cin >> key;
            Node *node = table.get(key);
            if (node != nullptr){
                cout << endl;
                node->show();
                cout << endl;
            } else cout << "\nThere is NO element with such KEY\n";
        } else if (operation == "--del"){
            if (!created){
                cout << "\nTABLE is NOT created\n";
                continue;
            }
            key_t key;
            cin >> key;
            Node *node = table.remove(key);
            if (node == nullptr) {
                cout << "\nThere is NO element with such KEY\n";
                continue;
            }
            cout << "\nYou deleted element with key = " << key;
            cout << "\nDeleted element: ";
            node->show();
            cout << "\nYour TABLE:";
            table.show();
            delete node;
        } else if (operation == "--clear"){
            if (!created){
                cout << "\nTABLE is NOT created\n";
                continue;
            }
            if (table.clear()) cout << "\nTABLE is clear\n";
            else cout << "\nTABLE is NOT clear\n";
        } else if (operation == "--show"){
            if (!created){
                cout << "\nTABLE is NOT created\n";
                continue;
            }
            table.show();
        }else if (operation == "--exit"){
            break;
        } else cout << "\nWRONG operation\n";
    }
    return 0;
}