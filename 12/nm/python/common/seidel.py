import numpy as np
from common.main import Matrix, MatrixOrientedMethod, Row
from common.utils import is_convergent, print_header


class SeidelMethod(MatrixOrientedMethod):

    def __init__(self, A: Matrix, B: Row) -> None:
        super().__init__(A, B)
        self.method_name = "Seidel"

        if not is_convergent(self.A):
            raise ValueError("A is not convergent")

    def execute_method(self, eps=1e-3, max_iterations=1000):
        x = np.zeros_like(self.B, dtype=np.double)

        for k in range(max_iterations):
            print_header(f"\nIteration {k}")
            print(f"x={x}")

            x_old = x.copy()

            for i in range(self.A.shape[0]):
                x[i] = (self.B[i] - np.dot(self.A[i, :i], x[:i]) - np.dot(
                    self.A[i, (i + 1):], x_old[(i + 1):])) / self.A[i, i]

            if np.linalg.norm(x - x_old, ord=np.inf) / np.linalg.norm(
                    x, ord=np.inf) < eps:
                break

        return x
