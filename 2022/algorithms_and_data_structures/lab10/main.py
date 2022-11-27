# Варіант 7
#
# Дано одновимірний масив цілих чисел A[і], де і =1,2,…,n.
# Знайти елемент що дорівнює різниці максимального та мінімального елементів.
# Вивести позицію шуканого елемента.

import random


def gen_random_int_array(n):
    return [random.randint(1, n) for _ in range(0, n)]


def gen_input_data():
    n = int(input("Enter array size: ") or 100)

    arr = gen_random_int_array(n)
    arr.sort()

    min_max_diff_el = arr[-1] - arr[0]

    print(f"Sorted generated array: {arr}")
    print(f"Min and max element difference: {min_max_diff_el}")

    return arr, min_max_diff_el


def binary_search(arr, key):
    comparisons = 0
    left, right = 0, len(arr) - 1
    while left <= right:
        comparisons += 1
        mid = (left + right) // 2
        print(f"Left={left}, Middle={mid}, Right={right}")
        if arr[mid] > key:
            comparisons += 2
            right = mid - 1
        elif arr[mid] < key:
            comparisons += 1
            left = mid + 1
        else:
            comparisons += 2
            return mid, comparisons

    return -1, comparisons


if __name__ == "__main__":
    arr, min_max_diff_el = gen_input_data()

    print()
    print("Searching in array for minmax diff element with binary search...")
    print()

    print("Binary search process:")
    found_idx, comparisons = binary_search(arr, min_max_diff_el)
    print()

    print(
        f"Found under id: {found_idx}, comparisons: {comparisons}"
        if found_idx != -1
        else "Minmax diff element was not found in the provided array"
    )
