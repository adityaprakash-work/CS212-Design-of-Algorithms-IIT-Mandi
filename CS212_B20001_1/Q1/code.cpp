// CS212 Assignment 1: Question 1, Aditya Prakash B20001
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

const int THRESHOLD = 2 * log2(10);

int ThresholdExceededCount = 0;

// Function to partition the array
int partition(std::vector<int> &arr, int low, int high)
{
    int pivotIndex = rand() % (high - low + 1) + low;
    int pivot = arr[pivotIndex];
    std::swap(arr[pivotIndex], arr[high]);

    int i = low;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            std::swap(arr[i], arr[j]);
            i++;
        }
    }
    std::swap(arr[i], arr[high]);
    return i;
}

// Function to perform quicksort
void quicksort(std::vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        int subArraySize = pivotIndex - low + 1;

        // Check if the threshold is exceeded
        if (high - low + 1 > THRESHOLD)
        {
            if (subArraySize > 1)
            {
                quicksort(arr, low, pivotIndex - 1);
            }
            if (high - pivotIndex > 1)
            {
                quicksort(arr, pivotIndex + 1, high);
            }
            else
            {
                // Swap the elements directly if the remaining subarray is small
                int temp = arr[low];
                arr[low] = arr[high];
                arr[high] = temp;
            }
            ThresholdExceededCount++;
        }
        else
        {
            quicksort(arr, low, pivotIndex - 1);
            quicksort(arr, pivotIndex + 1, high);
        }
    }
}

// Driver code
int main()
{
    int n;
    std::cout << "Enter the size of the array: ";
    std::cin >> n;

    std::vector<int> arr(n);

    std::cout << "Enter " << n << " elements separated by spaces: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    srand(static_cast<unsigned>(time(nullptr)));

    quicksort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "The threshold was exceeded " << ThresholdExceededCount << " times." << std::endl;

    return 0;
}
