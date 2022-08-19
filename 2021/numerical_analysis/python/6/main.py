#!/usr/bin/env python3

import numpy as np
from common.least_square import LeastSquareMethod

if __name__ == "__main__":
    A = np.array(
        [
            [-1, 5, 2],
            [4, 3, -1],
            [-1, 2, -1],
            [-1, 4, -3],
            [1, 2, -1],
        ],
        dtype=np.double,
    )

    B = np.array([1, 1, 12, -4, 9], dtype=np.double)

    for method in [LeastSquareMethod]:
        method(A, B).compile()
