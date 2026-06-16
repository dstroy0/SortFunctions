# SortFunctions Library

An Arduino library providing multiple sorting algorithm implementations for integer arrays.

## Features

- Five sorting algorithms: bubble, selection, insertion, quick, and merge sort
- Input validation guards (enabled by default, zero-cost opt-out)
- No dynamic allocation except within merge sort's internal merge step
- C++11 compatible
- Tested with an automated host-side test suite (159 test cases)

## Installation

1. Download or clone this repository
2. Copy the `SortFunctions` folder to your Arduino libraries directory
3. Restart the Arduino IDE
4. The library will be available under **Sketch > Include Library**

## Input Guards

All public functions validate their inputs before operating. Guards are **enabled by default** and can be disabled per translation unit to save a few bytes on very memory-constrained boards.

To disable, define the macro **before** including the header:

```cpp
#define SORTFUNCTIONS_INPUT_GUARDS 0
#include <SortFunctions.h>
```

When guards are enabled each function returns immediately (no-op) if:

| Condition | Applies to |
|-----------|-----------|
| `arr == NULL` | all functions |
| `n <= 0` | `bubbleSort`, `selectionSort`, `insertionSort`, `sortArray` |
| `low < 0` or `high < low` | `quickSort` |
| `left < 0` or `right < left` | `mergeSort` |

## Functions

### `sortArray(int arr[], int n)`

Generic sort — uses bubble sort by default.

```cpp
int arr[] = {64, 34, 25, 12, 22, 11, 90};
sortArray(arr, 7);
```

### `bubbleSort(int arr[], int n)`

Simple comparison sort. Best for very small arrays or nearly-sorted data where code size matters most. O(n²) average/worst, O(n) best.

```cpp
bubbleSort(arr, 7);
```

### `selectionSort(int arr[], int n)`

Always performs O(n²) comparisons but minimises writes — useful when write cost is high. O(n²) all cases.

```cpp
selectionSort(arr, 7);
```

### `insertionSort(int arr[], int n)`

Efficient for small arrays and nearly-sorted data. O(n) best, O(n²) average/worst.

```cpp
insertionSort(arr, 7);
```

### `quickSort(int arr[], int low, int high)`

Fast in-place sort. O(n log n) average, O(n²) worst case (already-sorted input with last-element pivot).

```cpp
quickSort(arr, 0, 6);   // low = 0, high = size - 1
```

### `mergeSort(int arr[], int left, int right)`

Consistent O(n log n) in all cases. Internally allocates two temporary heap buffers during each merge step via `malloc`/`free`; on low-SRAM boards prefer `insertionSort` or `quickSort` if heap is tight.

```cpp
mergeSort(arr, 0, 6);   // left = 0, right = size - 1
```

## Usage Example

```cpp
#include <SortFunctions.h>

void setup() {
    Serial.begin(9600);

    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size  = 7;

    quickSort(arr, 0, size - 1);

    for (int i = 0; i < size; i++) {
        Serial.println(arr[i]);
    }
}

void loop() {}
```

## Algorithm Comparison

| Algorithm      | Best       | Average    | Worst      | Extra memory | Stable |
|----------------|------------|------------|------------|--------------|--------|
| Bubble Sort    | O(n)       | O(n²)      | O(n²)      | O(1)         | Yes    |
| Selection Sort | O(n²)      | O(n²)      | O(n²)      | O(1)         | No     |
| Insertion Sort | O(n)       | O(n²)      | O(n²)      | O(1)         | Yes    |
| Quick Sort     | O(n log n) | O(n log n) | O(n²)      | O(log n)     | No     |
| Merge Sort     | O(n log n) | O(n log n) | O(n log n) | O(n) heap    | Yes    |

## Testing

A host-side test suite lives in `tests/`. It requires `g++` and covers 159 test cases per the standard sorting scenarios plus input guard validation.

**Windows** (MinGW-w64 / MSYS2 `g++` on PATH):

```bat
tests\run_tests.bat
```

**Linux / macOS**:

```bash
bash tests/run_tests.sh
```

The compiled test binary is removed automatically after each run.

## Examples

See the `examples/` folder for more usage examples.

## License

GNU Affero General Public License v3.0 — see [LICENSE](LICENSE) for details.
