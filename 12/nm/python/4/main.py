#!/usr/bin/env python3
from common.main import GaussianEliminationMethod

if __name__ == "__main__":
    A = [
        [0.83, 1.41, 0.58],
        [1.23, 0.83, 1.17],
        [1.43, 1.58, 0.83],
    ]
    B = [2.71, 5.26, 1.03]

    GaussianEliminationMethod(A, B).compile()
