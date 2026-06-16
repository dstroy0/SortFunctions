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

void setup()
{
    // Wait for serial port to connect (for boards with native USB)
    while (!Serial)
    {
        delay(1);
    }

    Serial.println("SortFunctions Library - Basic Example");
    Serial.println("=====================================");

    // Define an unsorted array
    int array[] = {64, 34, 25, 12, 22, 11, 90, 88};
    int size = sizeof(array) / sizeof(array[0]);

    // Print original array
    Serial.println("\nOriginal array:");
    printArray(array, size);

    // Sort the array using bubble sort
    bubbleSort(array, size);
    Serial.println("\nAfter Bubble Sort:");
    printArray(array, size);

    // Reset array for next example
    int array2[] = {64, 34, 25, 12, 22, 11, 90, 88};
    Serial.println("\nUsing Quick Sort:");
    quickSort(array2, 0, size - 1);
    printArray(array2, size);

    // Reset array for insertion sort
    int array3[] = {64, 34, 25, 12, 22, 11, 90, 88};
    Serial.println("\nUsing Insertion Sort:");
    insertionSort(array3, size);
    printArray(array3, size);
}

void loop()
{
    // Nothing to do in loop for this example
    delay(10000); // Delay to avoid spamming serial
}

// Helper function to print array
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
