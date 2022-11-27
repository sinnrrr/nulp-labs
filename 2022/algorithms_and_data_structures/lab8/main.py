import pprint
import random
from textwrap import dedent

from lab8.queue import Queue


def gen_input_data(n):
    low, high = 1, 1000
    return random.sample(range(low, high), n)


def show_statistics(q):
    min_el = max_el = q.items[0]
    next_max_el = None
    pre_min_el = None
    second_from_end = third_el = None
    n = len(q)

    for idx, el in enumerate(q.items):
        if idx == 2:
            third_el = el

        if idx == n - 2:
            second_from_end = el

        if min_el > el:
            min_el = el
            pre_min_el = q.items[idx - 1]

        if max_el < el:
            max_el = el
            next_max_el = q.items[idx + 1]

    print(
        dedent(
            f"""
          Elements count: {n}
          Min element: {min_el}
          Max element: {max_el}
          3rd element from the start: {third_el}
          2nd element from the end: {second_from_end}
          Pre-min element: {pre_min_el}
          Post-max element: {next_max_el}
          """
        )
    )


def populate_queue(n):
    q = Queue()
    data = gen_input_data(n)
    for char in data:
        q.enqueue(char)
    print("\nCreated Queue on array implementation\n")
    pp = pprint.PrettyPrinter(width=60, compact=True)
    print(f"Data acquired:\n {pp.pformat(data)}\n")
    return q


def main():
    q1 = populate_queue(100)
    q2 = populate_queue(200)

    print("Statistics:")
    show_statistics(q1)

    q1.merge(q2)
    print("Statistics after merge:")
    show_statistics(q1)


main()
