#include <iostream>

using namespace std;

string decode(string& message){
    string copy;
    for (char c : message) copy.push_back(c);
    for (int i = 1; i <= copy.size(); i *= 2) {
        int c = 0, n = 0, j = i - 1;
        while (j < copy.size()) {
            n++;
            if (copy[j] == '1') c++;
            if (n == i){
                n = 0;
                j += i + 1;
            } else j++;
        }
        if (c % 2 == 0) copy[i - 1] = copy[i - 1] == '1' ? '0' : '1';
    }
    int error = 0;
    for (int i = 1; i <= message.size(); i *= 2) if (message[i - 1] != copy[i - 1]) error += i;
    if (error) message[error - 1] = message[error - 1] == '1' ? '0' : '1';
    string result;
    for (int i = 1; i <= message.size(); i *= 2)
        for (int j = i; j < message.size(); ++j) {
            if (j == i * 2 - 1) break;
            result.push_back(message[j]);
        }
    return result;
}

void help(){
    cout << "It is Hamming decoder, it can:";
    cout << "\n--decode 'message' (decode binary message, encoded with Hamming code, example: 0100111100)";
    cout << "\n--help (show all commands)";
    cout << "\n--exit (exit the program)\n\n";
}

int main(){
    string command;
    help();
    while (true){
        cin >> command;
        if (command == "--decode"){
            string message;
            cin >> message;
            cout << "\nOriginal message: " << decode(message) << endl;
        } else if (command == "--help") help();
        else if (command == "--exit"){
            cout << "\nThe program is exited\n";
            break;
        } else cout << "\nNo such command\n";
    }
    return 0;
}
