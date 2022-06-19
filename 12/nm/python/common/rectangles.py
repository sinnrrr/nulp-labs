from typing import Callable, Dict, Literal, Tuple

import numpy as np
from common.main import IntegrationOrientedMethod

RectangleMethodType = Literal["right", "left", "centered", "trapezium"]


class RectangleMethod(IntegrationOrientedMethod):

    method_mappings: Dict[RectangleMethodType, Tuple[Callable, list[int]]]
    method_type: RectangleMethodType

    def __init__(self, method_type: RectangleMethodType, f: Callable, a: float,
                 b: float, eps: float) -> None:
        super().__init__(f"{method_type.capitalize()} rectangles", f, a, b,
                         eps)

        self.method_type = method_type
        self.method_mappings = {
            "left": (lambda i: self.f_xi(i), list(range(self.n - 1))),
            "right": (lambda i: self.f_xi(i), list(range(1, self.n))),
            "centered":
            (lambda i: self.f_xi(i + 0.5), list(range(self.n - 1))),
            "trapezium": (lambda i: (self.f_xi(i) + self.f_xi(i + 1)) / 2,
                          list(range(self.n - 1)))
        }

    def execute_method(self):
        return self.h * np.sum([
            self.method_mappings[self.method_type][0](i)
            for i in self.method_mappings[self.method_type][1]
        ])
