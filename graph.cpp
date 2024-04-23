#include <iostream>
#include <vector>
#include <map>

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
        cout << '\n';
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

    map<int, int> lowestDistanceToAll(int node){
        map<int, int>distances;
        vector<int>visited;
        int s = sumOfDistances();
        for (auto& n : this->nodes) {
            if (n.first != node) distances[n.first] = s + 1;
            for (int i : n.second) if (i != node) distances[i] = s + 1;
        }
        distances[node] = 0;
        deikrtra(visited, distances, node);
        return distances;
    }
};

//------------------------------------------------------------------------------------------------------------
void help(){
    cout << "\nThis is the PROGRAM for Graph, POSSIBLE commands:\n";
    cout << "\n--help (show all COMMANDS)";
    cout << "\n--add 'flag' 'node1' 'node2' 'weight' (add 'node1' and 'node2' and 'weight' between their"
            "'flag': '-o' oriented weight, only from 'node1' to 'node2'; '-n' non-oriented weight)";
    cout << "\n--to_all 'node' (show distance from 'node' to all nodes)";
    cout << "\n--to_other 'node1' 'node2' (show distance from 'node1' to 'node2')";
    cout << "\n--show (show Graph)";
    cout << "\n--exit (exit the PROGRAM)\n\n";
}

void add(Graph& graph){
    string flag;
    int node1, node2, weight;
    cin >> flag;
    if (scanf("%d%d%d", &node1, &node2, &weight) != 3) {
        cout << "\nIncorrect input\n";
        return;
    }
    if (flag == "-o") graph.add(node1, node2, weight);
    else if (flag == "-n"){
        graph.add(node1, node2, weight);
        graph.add(node2, node1, weight);
    } else cout << "\nIncorrect flag\n";
}

void toAll(Graph& graph){
    int node;
    if (scanf("%d", &node) != 1) {
        cout << "\nIncorrect input\n";
        return;
    }
    if (!graph.isSource(node)){
        cout << "\nNode " << node << " is not source for other nodes\n";
        return;
    }
    map<int, int>distances = graph.lowestDistanceToAll(node);
    cout << endl;
    int sumOfWeights = graph.sumOfDistances();
    for (auto& distance : distances) {
        if (distance.second < sumOfWeights + 1) cout << "to " << distance.first << ": " << distance.second << endl;
    }
    cout << endl;
}

void toOther(Graph& graph){
    int node1, node2;
    if (scanf("%d%d", &node1, &node2) != 2) {
        cout << "\nIncorrect input\n";
        return;
    }
    if (!graph.isSource(node1) or !graph.find(node2)){
        cout << "\n'node1' is not source or 'node2' is not in graph\n";
        return;
    }
    map<int, int>distances = graph.lowestDistanceToAll(node1);
    int sumOfWeights = graph.sumOfDistances();
    if (distances[node2] == sumOfWeights + 1){
        cout << "\nThere is no path from " << node1 << " to " << node2 << endl;
        return;
    }
    cout << endl << distances[node2] << endl;
}

void doCommand(string& command, Graph& graph){
    if (command == "--help") help();
    else if (command == "--add") add(graph);
    else if (command == "--to_all") toAll(graph);
    else if (command == "--to_other") toOther(graph);
    else if (command == "--show") graph.print();
    else cout << "\nWrong command\n";
}
//------------------------------------------------------------------------------------------------------------

int main(){
    Graph graph = Graph();
    help();
    string command;
    while (true){
        cin >> command;
        if (command == "--exit"){
            cout << "\nThe PROGRAM is exited\n";
            break;
        } else doCommand(command, graph);
    }
    return 0;
}
