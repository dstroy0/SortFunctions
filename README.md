# SortFunctions Library

A comprehensive Arduino library for sorting algorithms.

## Features

- Multiple sorting algorithm implementations
- Optimized for Arduino boards
- Easy to use API
- Well-documented examples

## Installation

1. Download or clone this repository
2. Copy the `SortFunctions` folder to your Arduino libraries directory
3. Restart the Arduino IDE
4. The library will be available under Sketch > Include Library

## Functions

### sortArray(int arr[], int n)

Generic sort function that uses bubble sort by default.

**Parameters:**

- `arr[]` - Array of integers to sort
- `n` - Number of elements in the array

**Example:**

```cpp
int array[] = {64, 34, 25, 12, 22, 11, 90};
int size = 7;
sortArray(array, size);
```

### bubbleSort(int arr[], int n)

Implements bubble sort algorithm. Simple but slower for large arrays.

**Parameters:**

- `arr[]` - Array of integers to sort
- `n` - Number of elements in the array

**Example:**

```cpp
int array[] = {64, 34, 25, 12, 22, 11, 90};
int size = 7;
bubbleSort(array, size);
```

### quickSort(int arr[], int low, int high)

Implements quick sort algorithm. Efficient for most cases with O(n log n) average complexity.

**Parameters:**

- `arr[]` - Array of integers to sort
- `low` - Starting index (usually 0)
- `high` - Ending index (usually size - 1)

**Example:**

```cpp
int array[] = {64, 34, 25, 12, 22, 11, 90};
int size = 7;
quickSort(array, 0, size - 1);
```

### mergeSort(int arr[], int left, int right)

Implements merge sort algorithm. Stable sort with consistent O(n log n) complexity.

**Parameters:**

- `arr[]` - Array of integers to sort
- `left` - Starting index (usually 0)
- `right` - Ending index (usually size - 1)

**Example:**

```cpp
int array[] = {64, 34, 25, 12, 22, 11, 90};
int size = 7;
mergeSort(array, 0, size - 1);
```

### selectionSort(int arr[], int n)

Implements selection sort algorithm. Simple algorithm with O(n²) complexity.

**Parameters:**

- `arr[]` - Array of integers to sort
- `n` - Number of elements in the array

**Example:**

```cpp
int array[] = {64, 34, 25, 12, 22, 11, 90};
int size = 7;
selectionSort(array, size);
```

### insertionSort(int arr[], int n)

Implements insertion sort algorithm. Efficient for small arrays and nearly sorted data.

**Parameters:**

- `arr[]` - Array of integers to sort
- `n` - Number of elements in the array

**Example:**

```cpp
int array[] = {64, 34, 25, 12, 22, 11, 90};
int size = 7;
insertionSort(array, size);
```

## Usage Example

```cpp
#include "SortFunctions.h"

void setup() {
  Serial.begin(9600);

  int array[] = {64, 34, 25, 12, 22, 11, 90};
  int size = 7;

  // Sort the array using default sort
  sortArray(array, size);

  // Print the sorted array
  Serial.println("Sorted array:");
  for(int i = 0; i < size; i++) {
    Serial.println(array[i]);
  }
}

void loop() {
}
```

## Algorithm Comparison

| Algorithm      | Best Case  | Average Case | Worst Case | Memory   | Stable |
| -------------- | ---------- | ------------ | ---------- | -------- | ------ |
| Bubble Sort    | O(n)       | O(n²)        | O(n²)      | O(1)     | Yes    |
| Quick Sort     | O(n log n) | O(n log n)   | O(n²)      | O(log n) | No     |
| Merge Sort     | O(n log n) | O(n log n)   | O(n log n) | O(n)     | Yes    |
| Selection Sort | O(n²)      | O(n²)        | O(n²)      | O(1)     | No     |
| Insertion Sort | O(n)       | O(n²)        | O(n²)      | O(1)     | Yes    |

## Examples

See the `examples` folder for more detailed usage examples and advanced techniques.

## License

GNU Affero General Public License v3.0 (AGPL-3.0)

See LICENSE file for details.
