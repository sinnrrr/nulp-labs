from math import fabs

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


class LUDecompositionMethod(MatrixOrientedMethod):

    def __init__(self, A: Matrix, B: Row) -> None:
        super().__init__(A, B)

        self.method_name = "LU decomposition"

    def lu_decompose(self):
        """
        Decomposes a matrix A by PA=LU
        """

        def pivotize(m):
            """
            Creates the pivoting matrix for m.
            """
            n = len(m)
            ID = [[float(i == j) for i in range(n)] for j in range(n)]
            for j in range(n):
                row = max(range(j, n), key=lambda i: abs(m[i][j]))
                if j != row:
                    ID[j], ID[row] = ID[row], ID[j]
            return ID

        n = len(self.A)

        L = np.zeros((n, n))
        U = np.zeros((n, n))
        P = np.asarray(pivotize(self.A))
        PA = np.dot(P, self.A)

        for j in range(n):
            L[j][j] = 1.0
            for i in range(j + 1):
                s1 = sum(U[k][j] * L[i][k] for k in range(i))
                U[i][j] = PA[i][j] - s1
            for i in range(j, n):
                s2 = sum(U[k][j] * L[i][k] for k in range(j))
                L[i][j] = (PA[i][j] - s2) / U[j][j]

        return L, U, P

    def lu_solve(self, L, U, P, B):

        def forward_sub(L, b):
            """solution to Lx = b
            L must be a lower-triangular matrix
            b must be a vector of the same leading dimension as L
            """
            n = len(L)
            x = np.zeros(n)
            for i in range(n):
                sum = 0
                for j in range(i):
                    sum += L[i, j] * x[j]
                x[i] = (b[i] - sum) / L[i, i]
            return x

        def back_sub(U, b):
            """solution to Ux = b
            U must be an upper-triangular matrix
            b must be a vector of the same leading dimension as U
            """
            n = len(U)
            x = np.zeros(n)
            for i in range(n - 1, -1, -1):
                sum = 0
                for j in range(n - 1, i, -1):
                    sum += U[i, j] * x[j]
                x[i] = (b[i] - sum) / U[i, i]
            return x

        y = forward_sub(L, np.dot(P, B))
        x = back_sub(U, y)

        return x

    def execute_method(self):
        L, U, P = self.lu_decompose()

        print_matrix(L, "L")
        print_matrix(U, "U")
        print_matrix(P, "P")
        print("\nIs LU = PA:", np.array_equal(np.dot(L, U), np.dot(P, self.A)))

        return self.lu_solve(L, U, P, self.B.copy())
