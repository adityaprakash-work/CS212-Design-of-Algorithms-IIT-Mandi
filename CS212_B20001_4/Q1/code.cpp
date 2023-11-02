// ---DEPENDENCIES--------------------------------------------------------------
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;


// ---PROBLEM-------------------------------------------------------------------
// Is Harry's claim that Dijkstra's algorithm would not fail when only the edges 
// from the sources are negative (assuming the sources have no incoming edges) a 
// valid assertion? Justify your answer.

// ---INPUT---------------------------------------------------------------------
// 1. First line contains N, M denoting no. of vertices and no. of edges.
// 2. Next M lines contains 3 integers i, j, w denoting an edge from i to j with
//    weight w.

// User generated
tuple<int, int, vector<tuple<int, int, int>>> userInput() {
    int N, M;
    cin >> N >> M;
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < M; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back(make_tuple(a, b, w));
    }
    return make_tuple(N, M, edges);
}

// Randomly generated
tuple<int, int, vector<tuple<int, int, int>>> randomInput() {
    int N = rand() % 10 + 1;
    int M = rand() % 10 + 1;
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < M; i++) {
        int a = rand() % N;
        int b = rand() % N;
        int w = rand() % 10;
        edges.push_back(make_tuple(a, b, w));
    }
    return make_tuple(N, M, edges);
}

// ---SOLUTION------------------------------------------------------------------
// Dijkstra's algorithm implementation
// Return the shortest path from source for each node in the graph.
vector<int> dijkstra(int N, int M, vector<tuple<int, int, int>> edges, int source) {
    vector<int> dist(N, INT_MAX);
    dist[source] = 0;
    for (int i = 0; i < N - 1; i++) {
        for (auto edge : edges) {
            int u, v, w;
            tie(u, v, w) = edge;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    return dist;
}

// ---MAIN----------------------------------------------------------------------
int main() {
    int N, M;
    vector<tuple<int, int, int>> edges;
    tie(N, M, edges) = userInput();
    // int N, M;
    // vector<tuple<int, int, int>> edges;
    // tie(N, M, edges) = randomInput();
    int source = 0;
    vector<int> dist = dijkstra(N, M, edges, source);
    for (int i = 0; i < N; i++) {
        cout << dist[i] << " ";
    }
    cout << endl;
    return 0;
}

// ---REFERENCES-----------------------------------------------------------------
// 1. https://math.stackexchange.com/questions/124344/dijkstras-algorithm-on-a-directed-graph-with-negative-edges-only-leaving-the-so
// 2. https://www.quora.com/How-do-you-prove-Dijkstra%E2%80%99s-algorithm-works-in-a-case-with-negative-edges-from-the-source-and-no-negative-cycles