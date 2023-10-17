// ---DEPENDENCIES--------------------------------------------------------------
#include <iostream>
#include <vector>
#include <tuple>
#include <random>

using namespace std;

// ---PROBLEM STATEMENT---------------------------------------------------------
// Implement Radix Sort Algorithm

// Expected Time Complexity: O(N)

// ---INPUT---------------------------------------------------------------------
// 1. An integer, 'n' (1 <= n <= 10^5), representing the number of elements in
//    the array.
// 2. 'n' space-separated integers, each representing an element of the array.
//    (-10^6 <= element <= 10^6)

// User generated
tuple<int, vector<int>> userInput()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    return make_tuple(n, arr);
}

// Random generated
vector<int> randomInput(int n)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1e6, 1e6);

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = dis(gen);
    }

    return arr;
}
// ---OUTPUT--------------------------------------------------------------------
// The sorted array in ascending order.

// To include negative integers:

// Source - https://stackoverflow.com/questions/15306665/radix-sort-for-negative-integers
// "You can treat the sign as a special kind of digit. You sort the pile on the 
// units, then the tens, etc. and finally on the sign. This does produce a reversed 
// order for the negatives, you then simply reverse the contents of that bucket. 
// It's how old mechanical card sorters worked."

// Source - https://stackoverflow.com/questions/23169231/right-lsb-radix-how-to-handle-the-2s-complement
// What you need to do is invert the comparison operation on the sign bit. For 
// every other bit, 0 < 1, but for the sign bit we use 1 < 0. As you sort bits 0 
// through 30 (for 32-bit integers, obviously), you sort the magnitude of that 
// integer. Not absolutely, because there's that one-shift, but relative to all 
// other integers of the same sign, which is all we need.


// getMax
int getMax(const vector<int>& arr) {
    int maxVal = arr[0];
    for (int x : arr) {
        maxVal = max(maxVal, x);
    }
    return maxVal;
}

// countSort
void countSort(vector<int>& arr, int exp) {
    const int base = 10;
    vector<int> count(2 * base, 0);
    vector<int> output(arr.size());
    for (int i = 0; i < arr.size(); ++i) {
        int idx = (arr[i] < 0) ? base - 1 - ((-arr[i] / exp) % base) : base + ((arr[i] / exp) % base);
        count[idx]++;
    }
    for (int i = 1; i < 2 * base; ++i) {
        count[i] += count[i - 1];
    }
    for (int i = arr.size() - 1; i >= 0; --i) {
        int idx = (arr[i] < 0) ? base - 1 - ((-arr[i] / exp) % base) : base + ((arr[i] / exp) % base);
        output[count[idx] - 1] = arr[i];
        count[idx]--;
    }
    arr = output;
}

// radixSort
void radixSort(vector<int>& arr) {
    const int base = 10;
    int maxVal = getMax(arr);
    if (maxVal < 0) {
        return;
    }
    for (int exp = 1; maxVal / exp > 0; exp *= base) {
        countSort(arr, exp);
    }
    // reverse(arr.begin(), arr.end());
}

// ---MAIN----------------------------------------------------------------------
int main()
{
    // User input
    // int n;
    // vector<int> arr;
    // tie(n, arr) = userInput();

    // Random input
    int n = 10;
    vector<int> arr = randomInput(n);

    // Print Inputs
    cout << "n: " << n << endl;
    cout << "Array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Solution
    radixSort(arr);

    // Print output
    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}