/*
  SortFunctions Test Suite

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

  Compilation (from project root):
    g++ -std=c++11 -Wall -I tests/ -I src/ \
        tests/test_main.cpp src/SortFunctions.cpp -o tests/test_runner

  Or use the provided scripts:
    Windows : tests\run_tests.bat
    Linux   : bash tests/run_tests.sh
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <climits>
#include <vector>
#include <algorithm>

#include "SortFunctions.h"

// ====================================================================
// Minimal test framework
// ====================================================================

static int g_total = 0;
static int g_passed = 0;
static int g_failed = 0;

static void separator(char ch, int n = 64)
{
    for (int i = 0; i < n; i++)
        putchar(ch);
    putchar('\n');
}

static void begin_section(const char *name)
{
    printf("\n[%s]\n", name);
}

static void print_vec(const char *label, const std::vector<int> &v)
{
    printf("    %s [", label);
    for (size_t i = 0; i < v.size(); i++)
    {
        if (i)
            printf(", ");
        printf("%d", v[i]);
    }
    printf("]\n");
}

static void check(const char *desc, bool ok)
{
    ++g_total;
    if (ok)
    {
        ++g_passed;
        printf("  [ PASS ] %s\n", desc);
    }
    else
    {
        ++g_failed;
        printf("  [ FAIL ] %s\n", desc);
    }
}

static void record(const char *desc, bool ok,
                   const std::vector<int> &input,
                   const std::vector<int> &actual,
                   const std::vector<int> &expected)
{
    ++g_total;
    if (ok)
    {
        ++g_passed;
        printf("  [ PASS ] %s\n", desc);
    }
    else
    {
        ++g_failed;
        printf("  [ FAIL ] %s\n", desc);
        if (input.size() <= 24)
        {
            print_vec("input:   ", input);
            print_vec("actual:  ", actual);
            print_vec("expected:", expected);
        }
        else
        {
            printf("    (n=%zu - too large to print inline)\n", input.size());
        }
    }
}

// ====================================================================
// Sort function wrappers  (uniform interface: fn(arr, n))
// ====================================================================

typedef void (*SortFn)(int[], int);

// quickSort takes (arr, low, high) — wrap for uniform testing
static void wrap_quickSort(int arr[], int n)
{
    if (n > 0)
        quickSort(arr, 0, n - 1);
}

// mergeSort takes (arr, left, right) — wrap for uniform testing
static void wrap_mergeSort(int arr[], int n)
{
    if (n > 0)
        mergeSort(arr, 0, n - 1);
}

// ====================================================================
// Verification helpers
// ====================================================================

static std::vector<int> ref_sort(std::vector<int> v)
{
    std::sort(v.begin(), v.end());
    return v;
}

static void run_case(const char *desc, SortFn fn, const std::vector<int> &input)
{
    std::vector<int> actual = input;
    std::vector<int> expected = ref_sort(input);
    if (!actual.empty())
        fn(actual.data(), static_cast<int>(actual.size()));
    record(desc, actual == expected, input, actual, expected);
}

// ====================================================================
// Test cases  (shared across all six algorithms)
// ====================================================================

struct Case
{
    const char *name;
    std::vector<int> data;
};

static std::vector<int> rand_vec(int n, unsigned seed, int lo = -1000, int hi = 1000)
{
    srand(seed);
    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[i] = lo + rand() % (hi - lo + 1);
    return v;
}

static std::vector<Case> make_cases()
{
    std::vector<Case> c;

    // ----- edge cases -----
    c.push_back({"empty (n=0)", {}});
    c.push_back({"single positive", {42}});
    c.push_back({"single negative", {-7}});
    c.push_back({"single zero", {0}});

    // ----- two-element cases -----
    c.push_back({"two sorted", {1, 2}});
    c.push_back({"two reverse", {2, 1}});
    c.push_back({"two equal", {5, 5}});

    // ----- ordering patterns -----
    c.push_back({"sorted 5", {1, 2, 3, 4, 5}});
    c.push_back({"reverse sorted 5", {5, 4, 3, 2, 1}});
    c.push_back({"ascending staircase", {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}});
    c.push_back({"descending staircase", {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}});
    c.push_back({"alternating high/low", {100, -100, 100, -100, 100, -100}});

    // ----- duplicates -----
    c.push_back({"all identical", {7, 7, 7, 7, 7, 7, 7}});
    c.push_back({"zeros only", {0, 0, 0, 0, 0}});
    c.push_back({"pi digits (some duplicates)", {3, 1, 4, 1, 5, 9, 2, 6}});
    c.push_back({"heavy duplicates", {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}});

    // ----- sign combinations -----
    c.push_back({"negatives only", {-5, -3, -8, -1, -9, -2, -4}});
    c.push_back({"mixed signs with zero", {-3, 5, -1, 0, 8, -4, 2, -7, 6}});

    // ----- boundary values -----
    c.push_back({"INT_MAX and INT_MIN", {INT_MAX, INT_MIN, 0, -1, 1}});
    c.push_back({"INT extremes two-element", {INT_MIN, INT_MAX}});

    // ----- larger random arrays (fixed seeds for reproducibility) -----
    c.push_back({"random 32  (seed  42)", rand_vec(32, 42)});
    c.push_back({"random 64  (seed  99)", rand_vec(64, 99)});
    c.push_back({"random 128 (seed   7)", rand_vec(128, 7)});
    c.push_back({"random 256 (seed  13)", rand_vec(256, 13)});

    return c;
}

// ====================================================================
// Section runner
// ====================================================================

static void run_section(const char *name, SortFn fn, const std::vector<Case> &cases)
{
    begin_section(name);
    for (const auto &c : cases)
        run_case(c.name, fn, c.data);
}

// ====================================================================
// Input guard tests  (compiled only when guards are enabled)
// ====================================================================

#if SORTFUNCTIONS_INPUT_GUARDS
static void test_guards()
{
    begin_section("input guards (SORTFUNCTIONS_INPUT_GUARDS=1)");

    int arr[5] = {5, 3, 1, 4, 2};

    // NULL pointer — each must return without crashing.
    // Reaching check() proves execution continued normally.
    bubbleSort(NULL, 5);
    check("bubbleSort    : NULL array", true);
    selectionSort(NULL, 5);
    check("selectionSort : NULL array", true);
    insertionSort(NULL, 5);
    check("insertionSort : NULL array", true);
    quickSort(NULL, 0, 4);
    check("quickSort     : NULL array", true);
    mergeSort(NULL, 0, 4);
    check("mergeSort     : NULL array", true);
    sortArray(NULL, 5);
    check("sortArray     : NULL array", true);

    // n < 0 — must return without crashing or modifying arr
    bubbleSort(arr, -1);
    check("bubbleSort    : n < 0", true);
    selectionSort(arr, -1);
    check("selectionSort : n < 0", true);
    insertionSort(arr, -1);
    check("insertionSort : n < 0", true);
    sortArray(arr, -1);
    check("sortArray     : n < 0", true);

    // Invalid range — must return without crashing
    quickSort(arr, 3, 1);
    check("quickSort     : low > high", true);
    mergeSort(arr, 3, 1);
    check("mergeSort     : left > right", true);
    quickSort(arr, -1, 4);
    check("quickSort     : low < 0", true);
    mergeSort(arr, -1, 4);
    check("mergeSort     : left < 0", true);

    // Verify arr is unmodified after every invalid call above
    int expected[5] = {5, 3, 1, 4, 2};
    check("arr unmodified after all invalid calls",
          memcmp(arr, expected, sizeof(arr)) == 0);
}
#endif

// ====================================================================
// main
// ====================================================================

int main()
{
    separator('=');
    printf("  SortFunctions Library - Test Suite\n");
    separator('=');

    auto cases = make_cases();

    run_section("bubbleSort", bubbleSort, cases);
    run_section("selectionSort", selectionSort, cases);
    run_section("insertionSort", insertionSort, cases);
    run_section("quickSort", wrap_quickSort, cases);
    run_section("mergeSort", wrap_mergeSort, cases);
    run_section("sortArray", sortArray, cases);

#if SORTFUNCTIONS_INPUT_GUARDS
    test_guards();
#endif

    printf("\n");
    separator('=');
    printf("  Results : %d passed, %d failed, %d total\n",
           g_passed, g_failed, g_total);
    if (g_failed == 0)
        printf("  Status  : ALL TESTS PASSED\n");
    else
        printf("  Status  : %d TEST(S) FAILED\n", g_failed);
    separator('=');
    printf("\n");

    return (g_failed == 0) ? 0 : 1;
}
