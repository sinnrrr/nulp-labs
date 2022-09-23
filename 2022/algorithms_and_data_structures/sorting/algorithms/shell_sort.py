"""
2  9  3  5  8  1 gap=floor(3 /2) 1.4 ==1

2   ---     5
   8  ---      9
     1         3

2 8 1 5 9 3 gap = 1
"""


def shell_sort(arr, comparator):
    sublistcount = len(arr) // 2
    while sublistcount > 0:
        for start_position in range(sublistcount):
            yield from gap_insertion_sort(
                arr, start_position, sublistcount, comparator
            )
        sublistcount = sublistcount // 2


def gap_insertion_sort(nlist, start, gap, comparator):
    for i in range(start + gap, len(nlist), gap):

        current_value = nlist[i]
        position = i

        while position >= gap and comparator(
            nlist[position - gap], current_value
        ):
            nlist[position] = nlist[position - gap]
            position = position - gap
            yield nlist

        nlist[position] = current_value
        yield nlist
