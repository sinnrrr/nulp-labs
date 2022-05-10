from math import fabs

import numpy as np
from common.main import Matrix, MatrixOrientedMethod, Row
from common.utils import print_header, print_matrix


class GaussianEliminationMethod(MatrixOrientedMethod):

    def __init__(self, A: Matrix, B: Row) -> None:
        super().__init__(A, B)

        self.method_name = "Gaussian elimination"

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

            print_header(f"\nIteration {k}")
            print_matrix(self.A, "A")
            print_matrix([self.B], "B")

        # backward substitution
        x = np.zeros(n)
        for k in range(n - 1, -1, -1):
            x[k] = (self.B[k] -
                    np.dot(self.A[k, k + 1:n], x[k + 1:n])) / self.A[k, k]

        return x
