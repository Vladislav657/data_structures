#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Graph{
private:
    map<int, vector<int>>nodes;
    map<string, int>weights;

public:
    Graph() = default;

    void add(int node1, int node2, int weight){
        this->weights[to_string(node1) + '-' + to_string(node2)] = weight;
        this->nodes[node1].push_back(node2);
    }

    void sortByDistance(int sourse, vector<int>& relates){
        int index, change;
        for (int i = 0; i < relates.size(); ++i) {
            index = i;
            for (int j = i + 1; j < relates.size(); ++j) {
                if (this->weights[to_string(sourse) + '-' + to_string(relates[j])] <
                        this->weights[to_string(sourse) + '-' + to_string(relates[index])]){
                    index = j;
                }
            }
            change = relates[i];
            relates[i] = relates[index];
            relates[index] = change;
        }
    }

    void print(){
        for (auto& pair : this->nodes) {
            cout << pair.first << ": ";
            for (int i = 0; i < pair.second.size(); ++i){
                if (i > 0) cout << ", ";
                cout << pair.second[i];
            }
            cout << "; ";
        }
        cout << '\n';
        for (auto& pair : this->weights) {
            cout << pair.first << ": " << pair.second << "; ";
        }
        cout << '\n';
    }

    bool find(int node){
        for (auto& pair : this->nodes) {
            if (pair.first == node) return true;
            for (auto n : pair.second) if (n == node) return true;
        }
        return false;
    }

    bool isSourse(int node){
        for (auto& pair : this->nodes) if (pair.first == node) return true;
        return false;
    }

    int sum(){
        int result = 0;
        for (auto &pair : this->weights) result += pair.second;
        return result;
    }

    vector<int> lowestDistanceToAll(int node){
        set<int>allNodes;
        for (auto& pair : this->nodes) {
            if (pair.first != node) allNodes.insert(pair.first);
            for (auto n : pair.second) if (n != node) allNodes.insert(n);
        }

    }
};


int main(){
    Graph graph = Graph();
    graph.add(8, 1, 38);
    graph.add(8, 2, 29);
    graph.add(2, 1, 57);
    graph.print();
    return 0;
}
