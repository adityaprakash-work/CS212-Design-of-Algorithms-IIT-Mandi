// CS212 Assignment 1: Question 2, Aditya Prakash B20001
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Solution 1: Saddleback search
// Time complexity: O(m + n)
// Since the longest path possible is m + n manhattan path from one corner to
// the diagonally opposite corner in worst case scenario.
// Space complexity: O(1)
// Since we are not using any extra space.
pair<int, int> saddleback_search(int arr[15][20])
{
    int x;
    cout << "Enter the integer to be searched:";
    cin >> x;

    int i = 0, j = 19;
    while (i < 15 && j >= 0)
    {
        if (arr[i][j] == x)
        {
            cout << "Found " << x << " at (" << i << ", " << j << ")" << endl;
            return make_pair(i, j);
        }
        else if (arr[i][j] > x)
        {
            j--;
        }
        else
        {
            i++;
        }
    }
    cout << "Not found" << endl;
    return make_pair(-1, -1);
}

// Solution 2: Comparing with Binary search
// Time complexity: O(m log n)
// Since we are doing binary search on each row. Merging is not feasible because
// the first element of the next row is not necessarily greater than the last
// element of the previous row.
// Space complexity: O(1)
// Since we are not using any extra space.
pair<int, int> binary_search(int arr[15][20])
{
    int x;
    cout << "Enter the integer to be searched:";
    cin >> x;

    int i = 0, j = 19;
    while (i < 15)
    {
        int low = 0, high = 19;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (arr[i][mid] == x)
            {
                cout << "Found " << x << " at (" << i << ", " << mid << ")" << endl;
                return make_pair(i, mid);
            }
            else if (arr[i][mid] > x)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        i++;
    }
    cout << "Not found" << endl;
    return make_pair(-1, -1);
}

// Driver code
int main()
{
    // Constructing 15 x 20 row and column wise sorted integer array
    const int rows = 15;
    const int cols = 20;
    int arr[rows][cols];
    int counter = 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = counter++;
        }
    }
    // Timing the two functions
    // Timing the binary_search function
    int numMeasurements = 10; // You can adjust the number of measurements
    int binaryTotalTime = 0;
    for (int i = 0; i < numMeasurements; i++)
    {
        auto start = high_resolution_clock::now();
        binary_search(arr);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        binaryTotalTime += duration.count();
    }
    cout << "Average time taken by binary_search: " << binaryTotalTime / numMeasurements << " microseconds" << endl;

    // Timing the saddleback_search function
    int saddlebackTotalTime = 0;
    for (int i = 0; i < numMeasurements; i++)
    {
        auto start = high_resolution_clock::now();
        saddleback_search(arr);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        saddlebackTotalTime += duration.count();
    }
    cout << "Average time taken by saddleback_search: " << saddlebackTotalTime / numMeasurements << " microseconds" << endl;

    return 0;
}
// Conclusion:
// Saddleback search is faster than binary search for x = 220 as an example.