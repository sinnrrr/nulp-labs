import matplotlib.animation as anim
import matplotlib.pyplot as plt

from sorting.config import (
    BAR_COLOR,
    DEFAULT_ARR_ELEMENTS_COUNT,
    DEFAULT_SPEED,
    algo_options,
    speed_options,
)
from sorting.utils import Format


def ask_for_array_size(default_size=DEFAULT_ARR_ELEMENTS_COUNT):
    return int(
        input("\n" + Format.input("Enter the number of elements", default_size))
        or default_size
    )


def ask_for_speed(speed_options, default_speed=DEFAULT_SPEED):
    print("\n" + Format.header("Choose speed"))
    print(Format.speed_options(speed_options))

    default_speed = list(speed_options.values()).index(default_speed) + 1
    speed_options_key_list = list(speed_options)
    option_idx_selected = (
        int(
            input("\n" + Format.input("Enter the option number", default_speed))
            or default_speed
        )
        - 1
    )
    if option_idx_selected not in range(len(speed_options_key_list)):
        raise ValueError("Option is invalid")

    return speed_options[speed_options_key_list[option_idx_selected]]


def ask_for_algo(algo_options) -> int:
    print("\n" + Format.header("Choose algorithm"))
    print(Format.algo_options(algo_options))

    default_option = 1
    option_idx_selected = (
        int(
            input("\n" + Format.input("Enter the option number", default_option))
            or default_option
        )
        - 1
    )
    if option_idx_selected not in range(len(algo_options)):
        raise ValueError("Option is invalid")

    return option_idx_selected


def display_window(arr, n: int, gen, interval: int = DEFAULT_SPEED):
    # Initialize fig
    fig, ax = plt.subplots()
    fig.canvas.manager.set_window_title("Sorting Visualization")

    ax.set_title(title)

    bar_rec = ax.bar(range(len(arr)), arr, align="edge", color=BAR_COLOR)

    ax.set_xlim(0, n)
    ax.set_ylim(min(arr), max(arr) * 1.2)

    text = ax.text(0.01, 0.93, "", transform=ax.transAxes)

    epochs = [0]

    def update_plot(array, rec, epochs):
        for rec, val in zip(rec, array):
            if rec.get_height() != val:
                rec.set_height(val)
        epochs[0] += 1
        text.set_text("Operations count :{}".format(epochs[0]))
        print(f"{epochs[0]})", array)

    _ = anim.FuncAnimation(
        fig,
        func=update_plot,
        fargs=(bar_rec, epochs),
        frames=gen,
        interval=interval,
        repeat=False,
    )

    plt.show()


if __name__ == "__main__":
    n = ask_for_array_size()
    selected_algo_idx = ask_for_algo(algo_options)
    speed = ask_for_speed(speed_options)

    print("\n")

    title, algorithm, generator, comparator = algo_options[selected_algo_idx]
    arr = generator(n)
    res = algorithm(arr, comparator)

    display_window(arr, n, res, speed)
