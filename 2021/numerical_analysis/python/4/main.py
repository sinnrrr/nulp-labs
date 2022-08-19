#!/usr/bin/env python3

import numpy as np
from common.gaussian import GaussianEliminationMethod
from common.lu_decomposition import LUDecompositionMethod

if __name__ == "__main__":
    A = np.array([
        [0.13, -0.14, -2.00],
        [0.75, 0.18, 0.77],
        [0.28, -0.17, 0.39],
    ])
    B = np.array([0.15, 0.11, 0.12])

    for method in [GaussianEliminationMethod, LUDecompositionMethod]:
        method(A.copy(), B.copy()).compile()
