import numpy as np
from colorama import Fore, Style


def print_matrix(matrix, name: str):
    s = [[str(e) for e in row] for row in matrix]
    lens = [max(map(len, col)) for col in zip(*s)]
    fmt = "\t".join("{{:{}}}".format(x) for x in lens)
    table = [fmt.format(*row) for row in s]

    print(f"\n{name}:")
    print("\n".join(table))


def print_header(header: str):
    print(Fore.RED + header + Fore.RESET)


def print_method_introduction(name: str):
    print(f"\n\n{Fore.CYAN}>>> {name} method{Style.RESET_ALL}\n")


def is_convergent(E):
    norm1 = np.linalg.norm(E, ord=1)
    norm2 = np.linalg.norm(E, ord=np.inf)

    norm3 = 0
    for i in range(E.shape[0]):
        for j in range(E.shape[1]):
            if i != j:
                norm3 += abs((E[i, j] / E[i, i]))**2

    norms = [norm1, norm2, norm3]
    print(f"Norms: {norms}")

    return min(norms) < 1
