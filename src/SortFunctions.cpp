/*
  SortFunctions Library - Implementation

  Copyright (C) 2026 Douglas Quigg (dstroy0 dquigg123@gmail.com)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "SortFunctions.h"

// Bubble Sort Implementation
void bubbleSort(int arr[], int n)
{
#if SORTFUNCTIONS_INPUT_GUARDS
    if (arr == NULL || n <= 0)
        return;
#endif
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Selection Sort Implementation
void selectionSort(int arr[], int n)
{
#if SORTFUNCTIONS_INPUT_GUARDS
    if (arr == NULL || n <= 0)
        return;
#endif
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        // Swap
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }
}

// Insertion Sort Implementation
void insertionSort(int arr[], int n)
{
#if SORTFUNCTIONS_INPUT_GUARDS
    if (arr == NULL || n <= 0)
        return;
#endif
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort Helper
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Quick Sort Implementation
void quickSort(int arr[], int low, int high)
{
#if SORTFUNCTIONS_INPUT_GUARDS
    if (arr == NULL || low < 0 || high < low)
        return;
#endif
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort Helper
void merge(int arr[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int *leftArr = (int *)malloc(leftSize * sizeof(int));
    int *rightArr = (int *)malloc(rightSize * sizeof(int));

    if (!leftArr || !rightArr)
    {
        free(leftArr);
        free(rightArr);
        return;
    }

    for (int i = 0; i < leftSize; i++)
    {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < rightSize; i++)
    {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k++] = leftArr[i++];
        }
        else
        {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < leftSize)
    {
        arr[k++] = leftArr[i++];
    }

    while (j < rightSize)
    {
        arr[k++] = rightArr[j++];
    }

    free(leftArr);
    free(rightArr);
}

// Merge Sort Implementation
void mergeSort(int arr[], int left, int right)
{
#if SORTFUNCTIONS_INPUT_GUARDS
    if (arr == NULL || left < 0 || right < left)
        return;
#endif
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Default sort function
void sortArray(int arr[], int n)
{
#if SORTFUNCTIONS_INPUT_GUARDS
    if (arr == NULL || n <= 0)
        return;
#endif
    bubbleSort(arr, n);
}
