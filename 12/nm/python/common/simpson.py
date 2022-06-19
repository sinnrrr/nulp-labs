from typing import Callable

import numpy as np
from common.main import IntegrationOrientedMethod


class SimpsonMethod(IntegrationOrientedMethod):

    def __init__(self, f: Callable, a: float, b: float, eps: float) -> None:
        super().__init__("Simpson", f, a, b, eps)

    def execute_method(self):
        return (self.h / 3) * (
            self.f_xi(0) + self.f_xi(self.n) +
            4 * np.sum([self.f_xi(i - 1) for i in range(1, self.n) if i % 2]) +
            2 * np.sum([self.f_xi(i) for i in range(1, self.n - 1) if i % 2]))
