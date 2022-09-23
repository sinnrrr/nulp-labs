def swap(A, i, j):
    A[i], A[j] = A[j], A[i]


def insertion_sort(arr, comparator):
    """
    Iterate every element of the array, in inner loop look if
    current element is bigger/less then the previous element,
    if not -- check all of the prev elements and swap when found
    """
    if len(arr) == 1:
        return
    for i in range(1, len(arr)):
        j = i
        while j > 0 and comparator(arr[j - 1], arr[j]):
            swap(arr, j, j - 1)
            j -= 1
            yield arr
