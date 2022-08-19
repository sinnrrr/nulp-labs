#!/usr/bin/env python3

import numpy as np
from common.jakobi import JakobiMethod
from common.seidel import SeidelMethod

if __name__ == "__main__":
    # A = np.array([
    #     [0.81, -0.07, 0.38, -0.21],
    #     [-0.22, 0.78, 0.11, 0.33],
    #     [0.51, -0.07, 3.09, -0.11],
    #     [0.33, -0.41, 0.00, 0.83],
    # ])
    A = np.array([
        [0.55, 0, -0.08, 0.14],
        [0.3, -0.73, -0.12, 0.11],
        [0.17, 0.06, -0.58, 0.12],
        [0.21, -0.16, 0, 0.36],
    ])
    # B = np.array([0.81, -0.64, -1.71, -1.21])
    B = np.array([0.48, -1.24, -1.15, -0.88])

    for method in [SeidelMethod, JakobiMethod]:
        method(A, B).compile()
