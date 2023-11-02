// ---DEPENDENCIES--------------------------------------------------------------
#include <iostream>
#include <vector>
#include <tuple>


using namespace std;


// ---PROBLEM-------------------------------------------------------------------
// What is the minimum number of standard roads that need to be transformed into 
// super roads to achieve the "Great Administrator" status, where all cities in 
// the country are connected by roads, and the sum of maintenance costs does not 
// exceed a given limit K, while minimizing expenses by demolishing as many roads 
// as possible?

// ---INPUT---------------------------------------------------------------------
// 1. First line contains N, M, K denoting no. of cities, no. of roads, and the
//    limit on maintenance cost.
// 2. Next M lines contains 3 integers i, j, w denoting a road from i to j with
//    maintenance cost w.

// User generated
tuple<int, int, int, vector<tuple<int, int, int>>> userInput() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<tuple<int, int, int>> roads;
    for (int i = 0; i < M; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        roads.push_back(make_tuple(a, b, w));
    }
    return make_tuple(N, M, K, roads);
}

// Randomly generated
tuple<int, int, int, vector<tuple<int, int, int>>> randomInput() {
    int N = rand() % 10 + 1;
    int M = rand() % 10 + 1;
    int K = rand() % 10 + 1;
    vector<tuple<int, int, int>> roads;
    for (int i = 0; i < M; i++) {
        int a = rand() % N;
        int b = rand() % N;
        int w = rand() % 10;
        roads.push_back(make_tuple(a, b, w));
    }
    return make_tuple(N, M, K, roads);
}

// ---SOLUTION------------------------------------------------------------------
// Kruskal's algorithm implementation
// Return the minimum spanning tree of the graph.
vector<tuple<int, int, int>> kruskal(int N, int M, vector<tuple<int, int, int>> roads) {
    vector<tuple<int, int, int>> mst;
    vector<int> parent(N);
    for (int i = 0; i < N; i++) {
        parent[i] = i;
    }
    for (auto road : roads) {
        int u, v, w;
        tie(u, v, w) = road;
        if (parent[u] != parent[v]) {
            mst.push_back(road);
            int oldParent = parent[v];
            for (int i = 0; i < N; i++) {
                if (parent[i] == oldParent) {
                    parent[i] = parent[u];
                }
            }
        }
    }
    return mst;
}

// ---MAIN----------------------------------------------------------------------
int main() {
    int N, M, K;
    vector<tuple<int, int, int>> roads;
    tie(N, M, K, roads) = userInput();
    // int N, M, K;
    // vector<tuple<int, int, int>> roads;
    // tie(N, M, K, roads) = randomInput();
    vector<tuple<int, int, int>> mst = kruskal(N, M, roads);
    int cost = 0;
    for (auto road : mst) {
        int u, v, w;
        tie(u, v, w) = road;
        cost += w;
    }
    cout << cost << endl;
    return 0;
}


