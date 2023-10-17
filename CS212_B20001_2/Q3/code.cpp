// ---DEPENDENCIES--------------------------------------------------------------
#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <algorithm> // for std::sort

using namespace std;

// ---PROBLEM STATEMENT----------------------------------------------------------
// Median of Medians
// Given an array income[] of size N which denotes the money earned by N individuals 
// in a country. Government decides to exempt tax for people whose salary is less 
// than Kth largest income.
// a. So, find out the minimum income of the person who has to pay taxes.
// b. One of the people wants to find his/her rank based on the income M so also 
//    find that out, given the person's income and it is part of the income[] 
//    array.

// Expected Time Complexity: O(N)

// Note:
// 1. The input array arr may or may not be sorted & can have duplicates too. 
//    You have to find the Kth largest element in sorted order, not the distinct 
//    Kth largest element.
//    Source - https://stackoverflow.com/questions/14268693/quick-select-with-repeat-values
// 2. Also since elements can have the same value so in case of multiple ranks 
//    for a given value return the smallest rank.

// ---INPUT---------------------------------------------------------------------    
// 1. First line contains 3 space separated integers N, K and M denoting the
//    size of the array, the parameter K in the problem statement and parameter 
//    M in (b).
// 2. Next line contains N space separated integers where ith number denotes the
//    ith element of the input array, income[i].

// Constraints
// 1 <= N <= 10^3
// 1 <= K <= N
// 1 <= M <= 10^9
// 1 <= income[i] <= 10^9

// User generated
tuple<int, int, int, vector<int>> userInput() {
    int N, K, M;
    cin >> N >> K >> M;
    vector<int> income(N);
    for (int i = 0; i < N; i++) {
        cin >> income[i];
    }
    return make_tuple(N, K, M, income);
}

// Random generated
tuple<int, int, int, vector<int>> randomInput(int N) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1e5);
    uniform_int_distribution<> disKM(1, N);
    int K = disKM(gen);
    int MIndex = disKM(gen) - 1;
    vector<int> income(N);
    for (int i = 0; i < N; i++) {
        income[i] = dis(gen);
    }
    int M = income[MIndex];
    return make_tuple(N, K, M, income);
}

// ---OUTPUT--------------------------------------------------------------------
// a. A single integer denoting the found K th largest element of the
//    array.
// b. A single integer denoting the Rank of the person with the given
//    income.

// ---QUICKSELECT WITH MEDIAN OF MEDIANS----------------------------------------
// Quickselct with median of medians to find Kth largest element
int partition(vector<int>& arr, int left, int right, int pivot) {
    int pivotValue = arr[pivot];
    swap(arr[pivot], arr[right]);
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            swap(arr[storeIndex], arr[i]);
            storeIndex++;
        }
    }
    swap(arr[right], arr[storeIndex]);
    return storeIndex;
}

int medianOfMedians(vector<int>& arr, int left, int right, int k) {
    if (left == right) {
        return left;
    }
    int pivot = left + (right - left) / 2;
    pivot = partition(arr, left, right, pivot);
    if (k == pivot) {
        return k;
    }
    else if (k < pivot) {
        return medianOfMedians(arr, left, pivot - 1, k);
    }
    else {
        return medianOfMedians(arr, pivot + 1, right, k);
    }
}

int quickSelect(vector<int>& arr, int k) {
    int left = 0;
    int right = arr.size() - 1;
    int kthLargest = medianOfMedians(arr, left, right, arr.size() - k);
    return arr[kthLargest];
}

// ---MAIN----------------------------------------------------------------------
int main() {
    // User input
    // int N, K, M;
    // vector<int> income;
    // tie(N, K, M, income) = userInput();

    // Random input
    int N = 10;
    int K, M;
    vector<int> income(N);
    tie(N, K, M, income) = randomInput(N);

    // Solution (a)
    int kthLargest = quickSelect(income, K);
    // Solution (b)
    int rank = 1;
    for (int i = 0; i < N; i++) {
        if (income[i] > M) {
            rank++;
        }
    }

    // Print Inputs
    cout << "N: " << N << ", K: " << K << ", M: " << M << endl;
    cout << "Income: ";
    for (int i = 0; i < N; i++) {
        cout << income[i] << " ";
    }
    cout << endl;

    // Print sorted array (for sanity check)
    vector<int> sortedIncome = income;
    sort(sortedIncome.begin(), sortedIncome.end());
    cout << "Sorted Income: ";
    for (int i = 0; i < N; i++) {
        cout << sortedIncome[i] << " ";
    }
    cout << endl;

    // Print output
    cout << "Kth largest: " << kthLargest << endl;
    cout << "Rank of M: " << rank << endl;

    return 0;
}

