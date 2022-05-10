import numpy as np
from common.main import Matrix, MatrixOrientedMethod, Row
from common.utils import is_convergent, print_header


class JakobiMethod(MatrixOrientedMethod):

    def __init__(self, A: Matrix, B: Row) -> None:
        super().__init__(A, B)
        self.method_name = "Jakobi"

        if not is_convergent(self.A):
            raise ValueError("A is not convergent")

    def execute_method(self, eps=1e-3, max_iterations=10000):
        x = np.zeros_like(self.B, dtype=np.double)
        T = self.A - np.diag(np.diagonal(self.A))  # type: ignore

        for i in range(max_iterations):
            print_header(f"\nIteration {i}")
            print(f"x={x}")

            x_old = x.copy()

            x = (self.B - np.dot(T, x)) / np.diagonal(self.A)

            if np.linalg.norm(x - x_old, ord=np.inf) / np.linalg.norm(
                    x, ord=np.inf) < eps:
                break

        return x
