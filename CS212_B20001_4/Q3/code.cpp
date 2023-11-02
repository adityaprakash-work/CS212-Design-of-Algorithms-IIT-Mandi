// ---DEPENDENCIES--------------------------------------------------------------
#include <iostream>
#include <vector>
#include <tuple>
#include <stack>

using namespace std;

// ---PROBLEM-------------------------------------------------------------------
// The problem requires us to determine whether it is possible for all students 
// in a class to complete their DSA assignment, given that some students are 
// dependent on others for their assignment. The dependencies are given in the 
// form of pairs, where one student is dependent on another.

// ---INPUT---------------------------------------------------------------------
// 1. First line contains N, M denoting no. of students and no. of dependency 
// pairs.
// 2. Next M lines contains 2 integers i, j denoting i is dependent on j. 
// (0 - indexed)

// User generated 
tuple<int, int, vector<pair<int, int>>> userInput() {
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> dependencies;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        dependencies.push_back(make_pair(a, b));
    }
    return make_tuple(N, M, dependencies);
}

// Randomly generated 
tuple<int, int, vector<pair<int, int>>> randomInput() {
    int N = rand() % 10 + 1;
    int M = rand() % 10 + 1;
    vector<pair<int, int>> dependencies;
    for (int i = 0; i < M; i++) {
        int a = rand() % N;
        int b = rand() % N;
        dependencies.push_back(make_pair(a, b));
    }
    return make_tuple(N, M, dependencies);
}

// ---SOLUTION------------------------------------------------------------------
// Returns adjacency list representation from a list of pairs.
vector<vector<int>> make_graph(int N, vector<pair<int, int>>& dependencies) {
    vector<vector<int>> graph(N);
    for (auto dep : dependencies) {
        graph[dep.second].push_back(dep.first);
    }
    return graph;
}

// A DFS-based function to check if there is a cycle in the directed graph.
bool hasCycle(vector<vector<int>>& graph, int node, vector<bool>& onpath, vector<bool>& visited) {
    if (visited[node]) {
        return false;
    }
    onpath[node] = visited[node] = true;
    for (int neighbor : graph[node]) {
        if (onpath[neighbor] || hasCycle(graph, neighbor, onpath, visited)) {
            return true;
        }
    }
    return onpath[node] = false;
}

// Main function to check whether it's possible for all students to complete their assignment
bool canFinish(int N, vector<pair<int, int>>& dependencies) {
    vector<vector<int>> graph = make_graph(N, dependencies);
    vector<bool> onpath(N, false), visited(N, false);
    for (int i = 0; i < N; i++) {
        if (!visited[i] && hasCycle(graph, i, onpath, visited)) {
            return false;
        }
    }
    return true;
}

// ---MAIN----------------------------------------------------------------------
int main() {
    int N, M;
    vector<pair<int, int>> dependencies;

    // Input
    tie(N, M, dependencies) = randomInput();
    // Print input
    cout << "N = " << N << ", M = " << M << endl;
    cout << "Dependencies: " << endl;
    for (auto dep : dependencies) {
        cout << dep.first << " " << dep.second << endl;
    }
    if (canFinish(N, dependencies)) {
        cout << "Possible for all students to complete their assignments";
    }
    else {
        cout << "Not possible for all students to complete their assignments";
    }

    return 0;
}

// ---REFERENCES----------------------------------------------------------------
// 1. https://www.geeksforgeeks.org/find-whether-it-is-possible-to-finish-all-tasks-or-not-from-given-dependencies/