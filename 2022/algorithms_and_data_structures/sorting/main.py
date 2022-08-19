import random

import matplotlib.animation as anim
import matplotlib.pyplot as plt
from sorting.bubble_sort import bubble_sort
from sorting.count_sort import count_sort
from sorting.format import Format
from sorting.heap_sort import heap_sort
from sorting.insertion_sort import insertion_sort
from sorting.merge_sort import merge_sort
from sorting.quick_sort import quick_sort
from sorting.selection_sort import selection_sort
from sorting.shell_sort import shell_sort


def random_array(n):
    arr = [i + 1 for i in range(n)]
    random.shuffle(arr)

    return arr


def ask_for_array_input() -> tuple[list, int]:
    default_n = 100
    n = int(
        input("\n" + Format.input("Enter the number of elements", default_n))
        or default_n)

    return (random_array(n), n)


def ask_for_option_selection(options) -> int:
    print("\n" + Format.header("Choose algorithm"))
    print(Format.algo_options(options))

    default_option = 1
    option_idx_selected = int(
        input("\n" + Format.input("Enter the option number", default_option))
        or default_option) - 1
    if option_idx_selected not in range(len(options)):
        raise ValueError("Option is invalid")

    return option_idx_selected


def display_window(arr, n, gen):
    # Initialize fig
    fig, ax = plt.subplots()
    ax.set_title(title)

    bar_rec = ax.bar(range(len(arr)), arr, align='edge')

    ax.set_xlim(0, n)
    ax.set_ylim(0, int(n * 1.1))

    text = ax.text(0.02, 0.95, "", transform=ax.transAxes)

    epochs = [0]

    def update_plot(array, rec, epochs):
        for rec, val in zip(rec, array):
            rec.set_height(val)
        epochs[0] += 1
        text.set_text("No.of operations :{}".format(epochs[0]))

    _ = anim.FuncAnimation(fig,
                           func=update_plot,
                           fargs=(bar_rec, epochs),
                           frames=gen,
                           interval=1,
                           repeat=False)

    plt.show()


if __name__ == "__main__":
    arr, n = ask_for_array_input()

    options = [("Bubble sort", bubble_sort),
               ("Insertion sort", insertion_sort), ("Quick sort", quick_sort),
               ("Selection sort", selection_sort), ("Merge sort", merge_sort),
               ("Heap sort", heap_sort), ("Shell sort", shell_sort),
               ("Count sort", count_sort)]

    option_idx_selected = ask_for_option_selection(options)

    title, algorithm = options[option_idx_selected]
    res = algorithm(arr)

    display_window(arr, n, res)
