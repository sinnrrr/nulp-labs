import math
from typing import Callable

import numpy as np
from common.gaussian import GaussianEliminationMethod
from common.main import NonLinearEqSysOrientedMethod
from prettytable import PrettyTable


class NewtonIterationMethod(NonLinearEqSysOrientedMethod):

    def __init__(self, eqsys: list[Callable]):
        super().__init__("Newton iteration", eqsys)

    def execute_method(self, tolerance=1e-4):
        """
        1) May (x0, y0) -> approximate solution
           delta_x, delta_y -> corrections
        2) Delta(x0, y0) can be found from Jakobian (det of the Jakobi matrix)
        3) delta_x, delta_y -> using gaussian elimintaion method
        4) x_next = x + delta_x     y_next = y + delta_y
        """
        X = np.array([0, 0], dtype=float)

        def f(X):
            x, y = X
            return np.array(
                [math.cos(x) + y - 1.2, 2 * x - math.sin(y - 0.5) - 2])

        def Jf(X):
            x, y = X
            return np.array([[-math.sin(x + 0.5), 1], [2, math.cos(y - 2)]])

        X_delta = X.copy()
        t = PrettyTable(["Iteration", "X", "Y", "Precision"])

        result = None
        iterations = 0
        while True:
            iterations += 1
            A = Jf(X)
            B = f(X)
            X_delta = GaussianEliminationMethod(A, B).compile(silent=True)
            X -= X_delta
            x, y = X
            norm = np.linalg.norm(B)

            t.add_row([iterations, x, y, norm])

            if norm < tolerance:
                result = (x, y)
                break

        print(t)

        return result
