"""
There are various ways of doing this thing.

Pivot as the middle element:
Recursively selecting pivot as a middle element of the array and throwing
lower elements to the left and larger to the right.

Pivot as the last element:
Make two pointers. One remembers last element that is bigger than pivot and the
second one is iterative. If we occur element, that is lower than pivot, swap
the pointers and increment the last bigger element pointer.
When this process got to the end, swap pivot (last element) with the first
pointer.

Example:

"""


def swap(A, i, j):
    A[i], A[j] = A[j], A[i]


def quick_sort(arr, comparator):
    return _quick_sort(arr, 0, len(arr) - 1, comparator)


def _quick_sort(arr, p, q, comparator):
    if p >= q:
        return
    piv = arr[q]
    pivindx = p
    for i in range(p, q):
        if comparator(arr[i], piv):
            swap(arr, i, pivindx)
            pivindx += 1
        yield arr
    swap(arr, q, pivindx)
    yield arr

    yield from _quick_sort(arr, p, pivindx - 1, comparator)
    yield from _quick_sort(arr, pivindx + 1, q, comparator)
