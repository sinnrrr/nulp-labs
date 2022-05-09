import numpy as np
from common.utils import print_header, print_matrix, print_method_introduction

Row = list[float]
Matrix = list[Row]


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
        print(f"AX - B = {np.dot(self.A, result) - self.B}")

        return result
