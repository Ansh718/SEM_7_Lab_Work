#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int deterministicPartition(vector<int> &arr, int low, int high)
{
    int pivot = 0;
    pivot = arr[low];
    int left = 0;
    left = low + 1;
    int right = 0;
    right = high;
    while (true)
    {
        while (left <= right && arr[left] <= pivot)
        {
            left++;
        }
        while (left <= right && arr[right] >= pivot)
        {
            right--;
        }
        if (left > right)
        {
            break;
        }
        swap(arr[left], arr[right]);
    }
    swap(arr[low], arr[right]);
    return right;
}

void deterministicQuickSort(vector<int> &arr, int low, int high, int &comparisons, int &swaps)
{
    if (low < high)
    {
        int pivotIndex = deterministicPartition(arr, low, high);
        comparisons += (high - low);
        swaps += 2;
        deterministicQuickSort(arr, low, pivotIndex - 1, comparisons, swaps);
        deterministicQuickSort(arr, pivotIndex + 1, high, comparisons, swaps);
    }
}

int randomizedPartition(vector<int> &arr, int low, int high)
{
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[low], arr[pivotIndex]);
    int pivot = arr[low];
    int left = low + 1;
    int right = high;
    while (true)
    {
        while (left <= right && arr[left] <= pivot)
        {
            left++;
        }
        while (left <= right && arr[right] >= pivot)
        {
            right--;
        }
        if (left > right)
        {
            break;
        }
        swap(arr[left], arr[right]);
    }
    swap(arr[low], arr[right]);
    return right;
}

void randomizedQuickSort(vector<int> &arr, int low, int high, int &comparisons, int &swaps)
{
    if (low < high)
    {
        int pivotIndex = randomizedPartition(arr, low, high);
        comparisons += (high - low);
        swaps += 2;
        randomizedQuickSort(arr, low, pivotIndex - 1, comparisons, swaps);
        randomizedQuickSort(arr, pivotIndex + 1, high, comparisons, swaps); 
    }
}

void printArray(const vector<int> &arr)
{
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;
}

int main()
{
    srand(time(0));
    int n = 0;
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int> arr1(n);
    cout << "Enter elements: \n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr1[i];
    }
    vector<int> arr2 = arr1;
    int ch = 0;
    while (1)
    {

        int comparisonsDet = 0, swapsDet = 0;
        int comparisonsRand = 0, swapsRand = 0;
        cout << "1.Deterministic Quick Sort\n2.Randomized Quick Sort\n3.Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Original array for deterministic quick sort:\n";
            printArray(arr1);
            deterministicQuickSort(arr1, 0, arr1.size() - 1, comparisonsDet,
                                   swapsDet);

            cout << "Sorted array (Deterministic):\n";
            printArray(arr1);
            cout << "Deterministic Quick Sort Comparisons: " << comparisonsDet
                 << endl;
            cout << "Deterministic Quick Sort Swaps: " << swapsDet << endl;
            break;
        case 2:
            cout << "\nOriginal array for randomized quick sort:\n";
            printArray(arr2);
            randomizedQuickSort(arr2, 0, arr2.size() - 1, comparisonsRand, swapsRand);
            cout << "Sorted array (Randomized):\n";
            printArray(arr2);
            cout << "Randomized Quick Sort Comparisons: " << comparisonsRand << endl;
            cout << "Randomized Quick Sort Swaps: " << swapsRand << endl;
            break;
        case 3:
            exit(0);
            break;
        }
    }
    return 0;
}