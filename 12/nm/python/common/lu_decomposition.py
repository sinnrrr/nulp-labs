import numpy as np
from common.main import MatrixOrientedMethod
from common.utils import back_sub, forward_sub, print_matrix


class LUDecompositionMethod(MatrixOrientedMethod):

    def __init__(self, A, B) -> None:
        super().__init__("LU decomposition", A, B)

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

    def execute_method(self):
        L, U, P = self.lu_decompose()

        print_matrix(L, "L")
        print_matrix(U, "U")
        print_matrix(P, "P")
        print("\nIs LU = PA:", np.array_equal(np.dot(L, U), np.dot(P, self.A)))

        y = forward_sub(L, np.dot(P, self.B.copy()))
        x = back_sub(U, y)

        return x
