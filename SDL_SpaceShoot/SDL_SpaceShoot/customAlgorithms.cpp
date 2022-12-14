#include "customAlgorithms.h"

using namespace std;

int partition(float arr[],Entity arr2[], int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
    swap(arr2[pivotIndex], arr2[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[pivotIndex], arr[start]);
            swap(arr2[pivotIndex], arr2[start]);
        }
    }

    return pivotIndex;
}

void quickSort(float arr[], Entity arr2[], int start, int end)
{

    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(arr,arr2, start, end);

    // Sorting the left part
    quickSort(arr, arr2, start, p - 1);

    // Sorting the right part
    quickSort(arr, arr2, p + 1, end);
}

bool binarySearch(float arr[], int l, int r, float playerPos)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        // If the element is present at the middle
        // itself
        if (arr[mid] == playerPos)
           return mid;

        //// If element is smaller than mid, then
        //// it can only be present in left subarray
        if (arr[mid] > playerPos)
            return binarySearch(arr, l, mid - 1, playerPos);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, playerPos);
    }

    // We reach here when element is not
    // present in array
    return -1;
}

