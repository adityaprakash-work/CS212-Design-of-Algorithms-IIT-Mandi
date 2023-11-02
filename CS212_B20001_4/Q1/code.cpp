// ---DEPENDENCIES--------------------------------------------------------------
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <limits>

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

const int INF = numeric_limits<int>::max();

vector<int> dijkstra(const int N, const int M, const vector<tuple<int, int, int>>& edges, const int start) {
    vector<int> dist(N, INF);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int v = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d != dist[v]) {
            continue;  // Skip outdated entries
        }

        for (const auto& edge : edges) {
            int a, b, w;
            tie(a, b, w) = edge;
            if (a == v && dist[a] + w < dist[b]) {
                dist[b] = dist[a] + w;
                pq.push({ dist[b], b });
            }
        }
    }

    return dist;
}

// ---MAIN----------------------------------------------------------------------
int main() {
    // int N, M;
    // vector<tuple<int, int, int>> edges;
    // tie(N, M, edges) = userInput();
    // int N, M;
    // vector<tuple<int, int, int>> edges;
    // tie(N, M, edges) = randomInput();
    // Sample input
    int N = 5, M = 6;
    vector<tuple<int, int, int>> edges = {
        {0, 1, 1},
        {0, 2, 2},
        {1, 2, 3},
        {1, 3, 4},
        {2, 3, 5},
        {3, 4, 6}
    };
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