from math import sinh
from typing import List

from common.rectangles import RectangleMethod, RectangleMethodType
from common.simpson import SimpsonMethod

if __name__ == "__main__":

    def f(x):
        return sinh(x) / (1 - 2 * x + pow(3 * x, 2))

    a = 0
    b = 2
    eps = 0.00001

    rectangle_methods: List[RectangleMethodType] = [
        "left", "right", "centered", "trapezium"
    ]

    for rectangle_method in rectangle_methods:
        RectangleMethod(rectangle_method, f, a, b, eps).compile()

    SimpsonMethod(f, a, b, eps).compile()
