// ---DEPENDENCIES--------------------------------------------------------------
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

// ---PROBLEM-------------------------------------------------------------------
// Given an array of N integers, and K commands. Each of the K commands can be 
// either:
// 1. An "Update": Change the value at a given position in the sequence.
// 2. An "Increment": Increase all the numbers of the sequence in a given range 
//    by some value.
// 3. A "Get": Get the value at a given position.

// Constraints: Each operation takes O(log(N)) time.

// ---INPUT---------------------------------------------------------------------
// User generated
// 1. 1st line contains 2 space separated integers N and K denoting the size of
//    the array and the number of commands respectively.
// 2. Next line contains N space separated integers denoting the initial array.
// 3. Next K lines contain one of the following:
//    a. "U" followed by 2 space separated integers i and v, denoting an update
//       operation. Update the value at position i to v.
//    b. "I" followed by 3 space separated integers i, j and v, denoting an
//       increment operation. Increment the values from index i to j by v.
//    c. "G" followed by an integer i, denoting a get operation. Get the value
//       at position i.
tuple <int, int, vector<int>, vector<tuple<char, int, int, int>>> userInput() {
    int N, K;
    cin >> N >> K;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    vector<tuple<char, int, int, int>> commands(K);
    for (int i = 0; i < K; i++) {
        char c;
        cin >> c;
        if (c == 'U') {
            int i, v;
            cin >> i >> v;
            commands[i] = make_tuple(c, i, v, 0);
        }
        else if (c == 'I') {
            int i, j, v;
            cin >> i >> j >> v;
            commands[i] = make_tuple(c, i, j, v);
        }
        else if (c == 'G') {
            int i;
            cin >> i;
            commands[i] = make_tuple(c, i, 0, 0);
        }
    }
    return make_tuple(N, K, arr, commands);
}

// Randomly generated
tuple <int, int, vector<int>, vector<tuple<char, int, int, int>>> randomInput() {
    int N = rand() % 1000 + 1;
    int K = rand() % 1000 + 1;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 1000 + 1;
    }
    vector<tuple<char, int, int, int>> commands(K);
    for (int i = 0; i < K; i++) {
        char c = rand() % 3;
        if (c == 0) {
            int i = rand() % N;
            int v = rand() % 1000 + 1;
            commands[i] = make_tuple(c, i, v, 0);
        }
        else if (c == 1) {
            int i = rand() % N;
            int j = rand() % N;
            int v = rand() % 1000 + 1;
            commands[i] = make_tuple(c, i, j, v);
        }
        else if (c == 2) {
            int i = rand() % N;
            commands[i] = make_tuple(c, i, 0, 0);
        }
    }
    return make_tuple(N, K, arr, commands);
}

// ---SOLUTION------------------------------------------------------------------
// Segment Tree: array implementation
// For increment operation, we use lazy propagation.

// Array implementation of segment tree
// We don't want to do complex queries like range sum, range min, etc., we just 
// want to do point/ range updates and get the value at a given index.

class SegmentTree {
private:
    std::vector<int> arr;
    std::vector<int> tree;
    std::vector<int> lazy;
    int n;

    const int INF = std::numeric_limits<int>::min();

    void build_tree(int node, int a, int b) {
        if (a > b) return;

        if (a == b) {
            tree[node] = arr[a];
            return;
        }

        build_tree(node * 2, a, (a + b) / 2);
        build_tree(node * 2 + 1, 1 + (a + b) / 2, b);

        tree[node] = std::max(tree[node * 2], tree[node * 2 + 1]);
    }

    void update_tree(int node, int a, int b, int i, int j, int value) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];

            if (a != b) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }

            lazy[node] = 0;
        }

        if (a > b || a > j || b < i)
            return;

        if (a >= i && b <= j) {
            tree[node] += value;

            if (a != b) {
                lazy[node * 2] += value;
                lazy[node * 2 + 1] += value;
            }

            return;
        }

        update_tree(node * 2, a, (a + b) / 2, i, j, value);
        update_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j, value);

        tree[node] = std::max(tree[node * 2], tree[node * 2 + 1]);
    }

    int query_tree(int node, int a, int b, int i, int j) {
        if (a > b || a > j || b < i) return INF;

        if (lazy[node] != 0) {
            tree[node] += lazy[node];

            if (a != b) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }

            lazy[node] = 0;
        }

        if (a >= i && b <= j)
            return tree[node];

        int q1 = query_tree(node * 2, a, (a + b) / 2, i, j);
        int q2 = query_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j);

        return std::max(q1, q2);
    }

public:
    SegmentTree(const std::vector<int>& input) {
        arr = input;
        n = input.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build_tree(1, 0, n - 1);
    }

    // updateIndex
    void update(int i, int value) {
        update_tree(1, 0, n - 1, i, i, value);
    }

    // incrementRange
    void icrementRange(int i, int j, int value) {
        update_tree(1, 0, n - 1, i, j, value);
    }

    // getIndex
    int getIndex(int i) {
        return query_tree(1, 0, n - 1, i, i);
    }
};

// ---MAIN----------------------------------------------------------------------
int main() {
    // User generated input
    // int N, K;
    // vector<int> arr;
    // vector<tuple<char, int, int, int>> commands;
    // tie(N, K, arr, commands) = userInput();

    // Randomly generated input
    // int N, K;
    // vector<int> arr;
    // vector<tuple<char, int, int, int>> commands;
    // tie(N, K, arr, commands) = randomInput();

    // Test input
    int N = 5;
    int K = 5;
    vector<int> arr = { 1, 2, 3, 4, 5 };
    vector<tuple<char, int, int, int>> commands = {
        make_tuple('U', 0, 101, 0),
        make_tuple('I', 1, 3, 10),
        make_tuple('G', 0, 0, 0),
        make_tuple('G', 1, 1, 0),
        make_tuple('G', 2, 2, 0)
    };

    SegmentTree st(arr);

    for (int i = 0; i < K; i++) {
        char c;
        int i1, i2, v;
        tie(c, i1, i2, v) = commands[i];
        if (c == 'U') {
            st.update(i1, v);
        }
        else if (c == 'I') {
            st.icrementRange(i1, i2, v);
        }
        else if (c == 'G') {
            cout << st.getIndex(i1) << endl;
        }
        // Print array
        for (int i = 0; i < N; i++) {
            cout << st.getIndex(i) << " ";
        }

    }

    return 0;
}

// ---REFERENCES----------------------------------------------------------------
// 1. YouTube - SecondThread
//    https://www.youtube.com/watch?v=QvgpIX4_vyA
// 2. GeeksforGeeks - Lazy Propagation in Segment Tree
//    https://www.geeksforgeeks.org/lazy-propagation-in-segment-tree/
// 3. se7so - Blog
//    https://se7so.blogspot.com/2012/12/segment-trees-and-lazy-propagation.html
