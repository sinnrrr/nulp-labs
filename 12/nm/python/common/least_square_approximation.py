import numpy as np
from common.lu_decomposition import LUDecompositionMethod
from common.main import ApproximationOrientedMethod, Points
from common.utils import print_matrix


class LeastSquareApproximation(ApproximationOrientedMethod):

    def __init__(self, points: Points, degree: int) -> None:
        super().__init__("Least square approximation", points, degree)

    def execute_method(self):
        x = self.points[0]
        y = self.points[1]

        m = self.degree + 1
        n = len(x)

        A = np.zeros((m, m))
        B = np.zeros(m)

        # composing normal eq system, using formula
        for k in range(m):
            for i in range(n):
                B[k] += y[i] * (x[i]**k)
                for j in range(m):
                    A[k][j] += x[i]**(j + k)

        print_matrix(A, "A")
        print_matrix([B], "B")

        # solving normal eq system using LU decomposition
        coeffs = LUDecompositionMethod(A, B).compile(silent=True)

        return np.poly1d(coeffs[::-1])
