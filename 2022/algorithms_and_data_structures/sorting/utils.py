import random

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


def random_continious_array(n):
    arr = [i + 1 for i in range(n)]
    random.shuffle(arr)

    return arr


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
            formatted_options.append(Fore.BLUE + str(idx + 1) + ") " +
                                     Fore.CYAN + option[0] + Style.RESET_ALL)

        return '\n'.join(formatted_options)

    @staticmethod
    def speed_options(options: dict) -> str:
        formatted_options = []

        i = 1
        for speed_alias in options.keys():
            formatted_options.append(Fore.BLUE + str(i) + ") " + Fore.CYAN +
                                     speed_alias + Style.RESET_ALL)
            i += 1

        return '\n'.join(formatted_options)

    @staticmethod
    def input(text, default_value):
        default_value_text = f" [{Fore.GREEN}{default_value}{Fore.BLUE}]" if default_value is not None else ""

        return Fore.BLUE + f"{text}{default_value_text}: " + Style.RESET_ALL
