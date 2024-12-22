#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct SortStats 
{
    long long comparisons = 0;
    long long exchanges = 0;
};

void bubbleSort(vector<int>& arr, SortStats& stats) 
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            stats.comparisons++;
            if (arr[j] > arr[j + 1]) 
            {
                swap(arr[j], arr[j + 1]);
                stats.exchanges++;
            }
        }
    }
}

void selectionSort(vector<int>& arr, SortStats& stats) 
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) 
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) 
        {
            stats.comparisons++;
            if (arr[j] < arr[minIndex]) 
            {
                minIndex = j;
            }
        }
        if (minIndex != i) 
        {
            swap(arr[i], arr[minIndex]);
            stats.exchanges++;
        }
    }
}

void insertionSort(vector<int>& arr, SortStats& stats) 
{
    int n = arr.size();
    for (int i = 1; i < n; i++) 
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            stats.comparisons++;
            arr[j + 1] = arr[j];
            j--;
            stats.exchanges++;
        }
        stats.comparisons++;
        arr[j + 1] = key;
    }
}

void heapify(vector<int>& arr, int n, int i, SortStats& stats) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) 
    {
        stats.comparisons++;
        if (arr[left] > arr[largest])
            largest = left;
    }

    if (right < n) 
    {
        stats.comparisons++;
        if (arr[right] > arr[largest])
            largest = right;
    }

    if (largest != i) 
    {
        swap(arr[i], arr[largest]);
        stats.exchanges++;
        heapify(arr, n, largest, stats);
    }
}

void heapSort(vector<int>& arr, SortStats& stats) 
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, stats);

    for (int i = n - 1; i > 0; i--) 
    {
        swap(arr[0], arr[i]);
        stats.exchanges++;
        heapify(arr, i, 0, stats);
    }
}

vector<int> generateRandomArray(int n) 
{
    vector<int> arr(n);
    for (int i = 0; i < n; i++) 
    {
        arr[i] = rand() % 100000;
    }
    return arr;
}

int main() 
{
    srand(time(0));

    vector<int> sizes = { 10, 100, 1000, 5000, 10000, 20000, 50000 };
    cout << left << setw(10) << "N";
    cout << setw(20) << "Bubble Sort";
    cout << setw(20) << "Selection Sort";
    cout << setw(20) << "Insertion Sort";
    cout << setw(20) << "Heap Sort" << endl;
    cout << left << setw(10) << "";
    cout << setw(10) << "Comp." << setw(10) << "Exch.";
    cout << setw(10) << "Comp." << setw(10) << "Exch.";
    cout << setw(10) << "Comp." << setw(10) << "Exch.";
    cout << setw(10) << "Comp." << setw(10) << "Exch." << endl;

    for (int n : sizes) 
    {
        vector<int> arr = generateRandomArray(n);

        SortStats bubbleStats, selectionStats, insertionStats, heapStats;

        vector<int> temp = arr;
        bubbleSort(temp, bubbleStats);

        temp = arr;
        selectionSort(temp, selectionStats);

        temp = arr;
        insertionSort(temp, insertionStats);

        temp = arr;
        heapSort(temp, heapStats);

        cout << left << setw(10) << n;
        cout << setw(10) << bubbleStats.comparisons << setw(10) << bubbleStats.exchanges;
        cout << setw(10) << selectionStats.comparisons << setw(10) << selectionStats.exchanges;
        cout << setw(10) << insertionStats.comparisons << setw(10) << insertionStats.exchanges;
        cout << setw(10) << heapStats.comparisons << setw(10) << heapStats.exchanges << endl;
    }

    return 0;
}
