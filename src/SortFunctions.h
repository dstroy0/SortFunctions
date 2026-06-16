/*
  SortFunctions Library
  A library for various sorting algorithm implementations

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

#ifndef SORTFUNCTIONS_H
#define SORTFUNCTIONS_H

#include <Arduino.h>

// Bubble Sort
void bubbleSort(int arr[], int n);

// Quick Sort
void quickSort(int arr[], int low, int high);

// Merge Sort
void mergeSort(int arr[], int left, int right);

// Selection Sort
void selectionSort(int arr[], int n);

// Insertion Sort
void insertionSort(int arr[], int n);

// Generic sort function (uses bubble sort by default)
void sortArray(int arr[], int n);

#endif // SORTFUNCTIONS_H
