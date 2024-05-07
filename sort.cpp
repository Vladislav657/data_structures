#include <iostream>
#include <vector>

using namespace std;

class Node{
public:
    double data;
    Node *left;
    Node *right;

    explicit Node(double data){
        this->data = data;
        this->left = this->right = nullptr;
    }
};

class BinaryTree{
public:
    Node *root;

    explicit BinaryTree(Node *root = nullptr){
        this->root = root;
    }

    void push(Node *node, int& inversions){
        if (this->root == nullptr) this->root = node;
        Node *current = this->root;
        while (true){
            inversions++;
            if (node->data < current->data){
                inversions++;
                if (current->left == nullptr){
                    current->left = node;
                    break;
                } else current = current->left;
            } else if (node->data > current->data){
                inversions++;
                if (current->right == nullptr){
                    current->right = node;
                    break;
                } else current = current->right;
            } else break;
        }
    }

    static void lrr(Node *node, vector<double>& sorted, int& inversions){
        inversions++;
        if (node == nullptr) return;
        lrr(node->left, sorted, inversions);
        sorted.push_back(node->data);
        lrr(node->right, sorted, inversions);
    }
};

vector<double> includeSort(vector<double> array){
    int inversions = 0;
    vector<double> sorted(array.size() + 1);
    for (int i = 1; i <= array.size(); ++i) sorted[i] = array[i - 1];
    double change;
    for (int i = 2; i < sorted.size(); ++i) {
        sorted[0] = sorted[i];
        for (int j = i; j > 0; --j) {
            inversions++;
            if (sorted[j] < sorted[j - 1]){
                change = sorted[j];
                sorted[j] = sorted[j - 1];
                sorted[j - 1] = change;
            } else break;
        }
    }
    for (int i = 0; i < sorted.size() - 1; ++i) sorted[i] = sorted[i + 1];
    sorted.pop_back();
    cout << "Include sort: " << inversions << endl;
    return sorted;
}

vector<double> choiceSort(vector<double> array){
    int inversions = 0;
    vector<double> sorted(array.size());
    for (int i = 0; i < array.size(); ++i) sorted[i] = array[i];
    double change;
    int index;
    for (int i = 0; i < sorted.size(); ++i) {
        index = i;
        for (int j = i + 1; j < sorted.size(); ++j) {
            inversions++;
            if (sorted[j] < sorted[index]) index = j;
        }
        change = sorted[i];
        sorted[i] = sorted[index];
        sorted[index] = change;
    }
    cout << "Choice sort: " << inversions << endl;
    return sorted;
}

vector<double> bubbleSort(vector<double> array){
    int inversions = 0;
    vector<double> sorted(array.size());
    for (int i = 0; i < array.size(); ++i) sorted[i] = array[i];
    double change;
    for (int i = 0; i < sorted.size() - 1; ++i) {
        for (int j = 1; j < sorted.size(); ++j){
            inversions++;
            if (sorted[j] < sorted[j - 1]){
                change = sorted[j];
                sorted[j] = sorted[j - 1];
                sorted[j - 1] = change;
            }
        }
    }
    cout << "Bubble sort: " << inversions << endl;
    return sorted;
}

vector<double> hoarSort(vector<double> array, int& inversions){
    vector<double>sorted;
    inversions++;
    if (array.size() < 2) for (double i : array) sorted.push_back(i);
    else {
        int index = (int) array.size() / 2;
        vector<double> left, right;
        for (int i = 0; i < array.size(); ++i) {
            inversions++;
            if (i == index) continue;
            if (array[i] < array[index]) left.push_back(array[i]);
            else right.push_back(array[i]);
        }
        left = hoarSort(left, inversions);
        right = hoarSort(right, inversions);
        for (double i : left) sorted.push_back(i);
        sorted.push_back(array[index]);
        for (double i : right) sorted.push_back(i);
    }
    return sorted;
}

vector<double> treeSort(vector<double>& array){
    int inversions = 0;
    BinaryTree bt = BinaryTree();
    vector<double>sorted;
    for (double i : array) bt.push(new Node(i), inversions);
    BinaryTree::lrr(bt.root, sorted, inversions);
    cout << "Tree sort: " << inversions << endl;
    return sorted;
}

int main(){
    int n = 10000;
    vector<double>arr(n);
    for (int i = 0; i < n; ++i) arr[i] = rand();

    vector<double>is = includeSort(arr);
    vector<double>cs = choiceSort(arr);
    vector<double>bs = bubbleSort(arr);
    vector<double>ts = treeSort(arr);

    int hoarInversions = 0;
    vector<double>hs = hoarSort(arr, hoarInversions);
    cout << "Hoar sort: " << hoarInversions << endl;

    return 0;
}
