from sorting.algorithms.bubble_sort import bubble_sort
from sorting.algorithms.count_sort import count_sort

# from sorting.heap_sort import heap_sort
# from sorting.insertion_sort import insertion_sort
from sorting.algorithms.merge_sort import merge_sort
from sorting.algorithms.quick_sort import quick_sort
from sorting.algorithms.selection_sort import selection_sort
from sorting.algorithms.shell_sort import shell_sort
from sorting.array_generators import gen_1, gen_2, gen_3, gen_4, gen_5, gen_6
from sorting.utils import Comparator

algo_options = [
    ("Bubble sort", bubble_sort, gen_1, Comparator.asc),
    ("Selection sort", selection_sort, gen_2, Comparator.desc),
    ("Shell sort", shell_sort, gen_3, Comparator.asc),
    ("Quick sort", quick_sort, gen_4, Comparator.alphbtcl),
    ("Merge sort", merge_sort, gen_5, Comparator.asc),
    ("Count sort", count_sort, gen_6, Comparator.asc),
    # ("Insertion sort", insertion_sort, generators[6]),
    # ("Heap sort", heap_sort),
]

speed_options = {"Slow": 1000, "Normal": 500, "Fast": 50, "BLAZINGLY FAST!!!": 1}

DEFAULT_ARR_ELEMENTS_COUNT = 10
DEFAULT_SPEED = speed_options["Normal"]
BAR_COLOR = "#B195D2"
