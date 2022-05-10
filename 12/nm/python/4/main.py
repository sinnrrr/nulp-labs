#!/usr/bin/env python3

from common.gaussian import GaussianEliminationMethod
from common.lu import LUDecompositionMethod

if __name__ == "__main__":
    A = [
        [0.13, -0.14, -2.00],
        [0.75, 0.18, 0.77],
        [0.28, -0.17, 0.39],
    ]
    B = [0.15, 0.11, 0.12]

    for method in [GaussianEliminationMethod, LUDecompositionMethod]:
        method(A, B).compile()
