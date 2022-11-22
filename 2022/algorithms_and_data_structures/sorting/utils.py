import random
import signal
import time

from colorama import Fore, Style


class Comparator:
    @staticmethod
    def asc(x, y):
        return x > y

    @staticmethod
    def desc(x, y):
        return x < y

    @staticmethod
    def alphbtcl(x, y):
        return Comparator.desc(x, y)


def random_real_array(n, include_negative=True):
    return [random.uniform(-n if include_negative else 0, n) for _ in range(n)]


def swap(A, i, j):
    a = A[j]
    A[j] = A[i]
    A[i] = a


class Format:
    @staticmethod
    def header(text: str) -> str:
        return Fore.RED + text + Style.RESET_ALL

    @staticmethod
    def algo_options(options) -> str:
        formatted_options = []

        for idx, option in enumerate(options):
            formatted_options.append(
                Fore.BLUE
                + str(idx + 1)
                + ") "
                + Fore.CYAN
                + option[0]
                + Style.RESET_ALL
            )

        return "\n".join(formatted_options)

    @staticmethod
    def speed_options(options: dict) -> str:
        formatted_options = []

        i = 1
        for speed_alias in options.keys():
            formatted_options.append(
                Fore.BLUE
                + str(i)
                + ") "
                + Fore.CYAN
                + speed_alias
                + Style.RESET_ALL
            )
            i += 1

        return "\n".join(formatted_options)

    @staticmethod
    def input(text, default_value):
        default_value_text = (
            f" [{Fore.GREEN}{default_value}{Fore.BLUE}]"
            if default_value is not None
            else ""
        )

        return Fore.BLUE + f"{text}{default_value_text}: " + Style.RESET_ALL


class TimeoutError(Exception):
    def __init__(self, value="Timed Out"):
        self.value = value

    def __str__(self):
        return repr(self.value)


def timeout(seconds_before_timeout):
    def decorate(f):
        def handler(signum, frame):
            raise TimeoutError()

        def new_f(*args, **kwargs):
            old = signal.signal(signal.SIGALRM, handler)
            old_time_left = signal.alarm(seconds_before_timeout)
            if (
                0 < old_time_left < seconds_before_timeout
            ):  # never lengthen existing timer
                signal.alarm(old_time_left)
            start_time = time.time()
            try:
                result = f(*args, **kwargs)
            finally:
                if (
                    old_time_left > 0
                ):  # deduct f's run time from the saved timer
                    old_time_left -= time.time() - start_time
                signal.signal(signal.SIGALRM, old)
                signal.alarm(old_time_left)
            return result

        # new_f.func_name = f.func_name
        return new_f

    return decorate
