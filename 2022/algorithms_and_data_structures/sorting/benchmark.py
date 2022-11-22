import timeit

from sorting.config import algo_options
from sorting.utils import Comparator, TimeoutError, random_real_array, timeout

sizes = [1024, 4096, 16384, 65336, 262144, 1048576, 4194304]
TIMEOUT = 60 * 5

timed_out = set()

for n in sizes:
    array = random_real_array(n)

    print(f"Running sorting with array of size {n}:")

    for sorting_info in algo_options:
        name, sort, _, _ = sorting_info
        if name in timed_out:
            print(f"{name}: timeout {TIMEOUT}sec")
            continue

        arr = array.copy()
        if name == "Count sort":
            arr = map(lambda e: abs(int(e)), arr)

        @timeout(TIMEOUT)
        def run_sorting():
            for _ in sort(arr, Comparator.asc):
                ...

        try:
            start = timeit.default_timer()
            run_sorting()
            stop = timeit.default_timer()
        except TimeoutError:
            timed_out.add(name)
            print(f"{name}: timeout {TIMEOUT}sec")
            continue

        print("{}: {:.5f}sec".format(name, (stop - start)))

    print()