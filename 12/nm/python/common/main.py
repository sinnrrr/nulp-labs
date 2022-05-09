from math import fabs

import numpy as np
from colorama import Fore, Style

Row = list[float]
Matrix = list[Row]


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
    print(f"{Fore.CYAN}>>> {name} method{Style.RESET_ALL}\n")


class Method:

    def compile(self):
        raise NotImplementedError

    def execute_method(self):
        raise NotImplementedError


class MatrixOrientedMethod(Method):
    A = np.array([])
    B = np.array([])

    method_name: str = "Unknown"

    def __init__(self, A: Matrix, B: Row) -> None:
        super().__init__()

        self.A = np.array(A)
        self.B = np.array(B)

        self.method_name = "Gaussian elimination"

    def execute_method(self):
        raise NotImplementedError

    def compile(self):

        print_method_introduction(self.method_name)

        print_header("Initial values")
        print_matrix(self.A, "A")
        print_matrix([self.B], "B")

        result = self.execute_method()

        print("\n")
        print_header("Resulting vectors")
        print(result)

        print("\n")
        print_header("Results verification")
        print("AX - B = " + np.dot(self.A, result) - self.B)


class GaussianEliminationMethod(MatrixOrientedMethod):

    def __init__(self, A: Matrix, B: Row) -> None:
        super().__init__(A, B)

    def execute_method(self):
        n = len(self.B)

        # Elimination phase
        for k in range(n - 1):
            # find the best raw
            for i in range(k + 1, n):
                if fabs(self.A[i, k]) > fabs(self.A[k, k]):
                    self.A[[k, i]] = self.A[[i, k]]
                    self.B[[k, i]] = self.B[[i, k]]
                    break

            for i in range(k + 1, n):
                if self.A[i, k] != 0.0:
                    cof = self.A[i, k] / self.A[k, k]
                    # calculate the new row
                    self.A[i] = self.A[i] - cof * self.A[k]
                    # update vector b
                    self.B[i] = self.B[i] - cof * self.B[k]

            print(f"\nIteration {k}:")
            print_matrix(self.A, "A")
            print_matrix([self.B], "B")

        # backward substitution
        x = np.zeros(n)
        for k in range(n - 1, -1, -1):
            x[k] = (self.B[k] -
                    np.dot(self.A[k, k + 1:n], x[k + 1:n])) / self.A[k, k]

        return x
