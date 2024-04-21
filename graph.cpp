#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Graph{
private:
    map<int, vector<int>>nodes;
    map<string, int>weights;


    static bool contains(vector<int>&v, int n){
        for (int i : v) if (i == n) return true;
        return false;
    }

    void deikrtra(vector<int>&visited, map<int, int>&distances, int node){
        this->sortByDistance(node);
        for (int i = 0; i < this->nodes[node].size(); ++i) {
            if (distances[node] + weights[to_string(node) + '-' + to_string(this->nodes[node][i])]
                < distances[this->nodes[node][i]]){
                distances[this->nodes[node][i]] = distances[node] +
                                                  weights[to_string(node) + '-' + to_string(this->nodes[node][i])];
            }
        }
        visited.push_back(node);
        for (int i : this->nodes[node]) {
            if (!contains(visited, i) && isSource(i))
                deikrtra(visited, distances, i);
        }
    }

public:
    Graph() = default;

    void add(int node1, int node2, int weight){
        this->weights[to_string(node1) + '-' + to_string(node2)] = weight;
        this->nodes[node1].push_back(node2);
    }

    void sortByDistance(int source){
        int index, change;
        for (int i = 0; i < this->nodes[source].size(); ++i) {
            index = i;
            for (int j = i + 1; j < this->nodes[source].size(); ++j) {
                if (this->weights[to_string(source) + '-' + to_string(this->nodes[source][j])] <
                        this->weights[to_string(source) + '-' + to_string(this->nodes[source][index])]){
                    index = j;
                }
            }
            change = this->nodes[source][i];
            this->nodes[source][i] = this->nodes[source][index];
            this->nodes[source][index] = change;
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

    bool isSource(int node){
        for (auto& pair : this->nodes) if (pair.first == node) return true;
        return false;
    }

    int sumOfDistances(){
        int result = 0;
        for (auto &pair : this->weights) result += pair.second;
        return result;
    }

    void lowestDistanceToAll(int node){
        map<int, int>distances;
        vector<int>visited;
        int s = sumOfDistances();
        for (auto& n : this->nodes) {
            if (n.first != node) distances[n.first] = s + 1;
            for (int i : n.second) if (i != node) distances[i] = s + 1;
        }
        distances[node] = 0;
        deikrtra(visited, distances, node);
        cout << "from " << node << endl;
        for (auto& distance : distances) {
            if (distance.second < s + 1) cout << "to " << distance.first << ": " << distance.second << endl;
        }
    }
};


int main(){
    Graph graph = Graph();
    graph.add(8, 1, 38);
    graph.add(8, 2, 29);
    graph.add(8, 3, 11);
    graph.add(8, 4, 9);
    graph.add(2, 1, 57);
    graph.add(2, 8, 39);
    graph.print();
    graph.lowestDistanceToAll(2);
    return 0;
}
