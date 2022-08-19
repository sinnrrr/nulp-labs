from typing import Callable

from common.main import NonLinearEqSysOrientedMethod
from common.utils import print_header
from prettytable import PrettyTable


class SimpleIterationMethod(NonLinearEqSysOrientedMethod):

    def __init__(self, eqsys: list[Callable]):
        super().__init__("Simple iterations", eqsys)

    def execute_method(self, tolerance=1e-4):
        """
        1) Making an approximate guess
        2) Linearly iterating using equeation function to get next x and y
        3) Checking if can be considered solution:
           (|x_next - x| + |y_next - y| < eps)
        """
        x, y = 0, 0

        print_header("Initial guess")
        print([x, y])
        print("\n")

        x_next, y_next = x, y
        iterations = 0

        f1, f2 = self.eqsys
        t = PrettyTable(["Iteration", "X", "Y", "Precision"])
        result = None

        while True:
            iterations += 1
            x_next, y_next = f2(y), f1(x)
            precision = abs(x_next - x) + abs(y_next - y)
            x, y = x_next, y_next

            t.add_row([iterations, x, y, precision])

            if precision < tolerance:
                result = (x, y)
                break

        print(t)

        return result
