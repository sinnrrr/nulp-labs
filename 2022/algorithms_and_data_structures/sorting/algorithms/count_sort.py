"""
1) Each cell of intermediate array is count of value
2) Modify the count array such that each element at each index stores the
sum of previous counts.
3) Shift right
4) Output: Key = Value + 1
"""

# 1 2 3 4 4 2 1

# 0 2 2 1 2
# 0 1 2 3 4

# 2 2 1 2
# 1 2 3 4

# 1 1 2 2 3 4 4


def count_sort(arr, _):
    max_val = max(arr)
    m = max_val + 1
    count = [0] * m

    for a in arr:
        count[a] += 1
        yield arr
    i = 0
    for a in range(m):
        for _ in range(count[a]):
            arr[i] = a
            i += 1
            yield arr
        yield arr
