import numpy as np
from common.main import Matrix, MatrixOrientedMethod, Row
from common.utils import print_matrix


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
