/*
  SortFunctions Library - Basic Example

  This example demonstrates how to use the SortFunctions library
  to sort an array of integers using different sorting algorithms.

  Circuit: None required (Serial output only)

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

void printArray(int arr[], int size)
{
    Serial.print("[ ");
    for (int i = 0; i < size; i++)
    {
        Serial.print(arr[i]);
        if (i < size - 1)
            Serial.print(", ");
    }
    Serial.println(" ]");
}

void setup()
{
    Serial.begin(9600);
    // Give native-USB boards (Leonardo, Zero, Due) up to 2 s to connect
    while (!Serial && millis() < 2000)
    {
    }

    Serial.println("SortFunctions Library - Basic Example");
    Serial.println("=====================================");

    int original[] = {64, 34, 25, 12, 22, 11, 90, 88};
    int size = sizeof(original) / sizeof(original[0]);

    Serial.println("\nOriginal array:");
    printArray(original, size);

    // Bubble Sort
    int arr1[] = {64, 34, 25, 12, 22, 11, 90, 88};
    bubbleSort(arr1, size);
    Serial.println("\nAfter Bubble Sort:");
    printArray(arr1, size);

    // Selection Sort
    int arr2[] = {64, 34, 25, 12, 22, 11, 90, 88};
    selectionSort(arr2, size);
    Serial.println("\nAfter Selection Sort:");
    printArray(arr2, size);

    // Insertion Sort
    int arr3[] = {64, 34, 25, 12, 22, 11, 90, 88};
    insertionSort(arr3, size);
    Serial.println("\nAfter Insertion Sort:");
    printArray(arr3, size);

    // Quick Sort
    int arr4[] = {64, 34, 25, 12, 22, 11, 90, 88};
    quickSort(arr4, 0, size - 1);
    Serial.println("\nAfter Quick Sort:");
    printArray(arr4, size);

    // Merge Sort
    int arr5[] = {64, 34, 25, 12, 22, 11, 90, 88};
    mergeSort(arr5, 0, size - 1);
    Serial.println("\nAfter Merge Sort:");
    printArray(arr5, size);
}

void loop()
{
    delay(10000);
}
