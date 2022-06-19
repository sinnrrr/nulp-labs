import math
from typing import Callable

import numpy as np
from common.utils import (blockPrint, enablePrint, print_header, print_matrix,
                          print_method_introduction)
from prettytable import PrettyTable

Row = list[float]
Matrix = list[Row]


class Method:
    method_name: str = "Unknown"

    def __init__(self, method_name: str) -> None:
        self.method_name = method_name

    def compile(self):
        raise NotImplementedError

    def execute_method(self):
        raise NotImplementedError


class MatrixOrientedMethod(Method):
    A = np.array([])
    B = np.array([])

    def __init__(self, method_name: str, A: np.ndarray, B: np.ndarray) -> None:
        super().__init__(method_name)

        self.A = A
        self.B = B

    def compile(self, silent=False):
        if silent:
            blockPrint()

        print_method_introduction(self.method_name)

        print_header("Initial values")
        print_matrix(self.A, "A")
        print_matrix([self.B], "B")

        result = self.execute_method()

        print("\n")
        print_header("Resulting vectors")
        print(result)

        print("\n")
        print_header("Results verification")
        print(f"AX - B = {np.dot(self.A, result) - self.B}")

        if silent:
            enablePrint()

        return result


class NonLinearEqSysOrientedMethod(Method):
    eqsys: list[Callable]

    def __init__(self, method_name: str, eqsys: list[Callable]):
        super().__init__(method_name)

        self.eqsys = eqsys

    def compile(self, silent=False):
        if silent:
            blockPrint()

        print_method_introduction(self.method_name)

        # print_header("Initial nonlinear equation system")
        # for eq in self.eqsys:
        #     dis(eq)
        # print("\n")

        result = self.execute_method()

        print("\n")
        print_header("Results")
        print(result)

        if silent:
            enablePrint()

        return result


Points = tuple[list[float], list[float]]


class InterpolationOrientedMethod(Method):
    points: Points
    x0: float

    def __init__(self, method_name: str, points: Points, x0: float) -> None:
        super().__init__(method_name)

        self.points = points
        self.x0 = x0

    def compile(self, silent=False):
        if silent:
            blockPrint()

        print_method_introduction(self.method_name)

        print_header("Initial values")
        x_points, y_points = self.points
        t = PrettyTable()
        t.add_column("X", x_points)
        t.add_column("Y", y_points)
        print(t)

        result = self.execute_method()

        print("\n")
        print_header("Results")
        print(result)

        if silent:
            enablePrint()

        return result


class ApproximationOrientedMethod(Method):
    points: Points
    degree: int

    def __init__(self, method_name: str, points: Points, degree: int) -> None:
        super().__init__(method_name)

        self.points = points
        self.degree = degree

    def compile(self, silent=False):
        if silent:
            blockPrint()

        print_method_introduction(
            f"{self.method_name} (degree of {self.degree})")

        print_header("Initial values")
        x_points, y_points = self.points
        t = PrettyTable()
        t.add_column("X", x_points)
        t.add_column("Y", y_points)
        print(t)

        result = self.execute_method()

        print("\n")
        print_header("Results")
        print(result)

        if silent:
            enablePrint()

        return result


class IntegrationOrientedMethod(Method):
    f: Callable
    a: float
    b: float
    eps: float

    def __init__(self, method_name: str, f: Callable, a: float, b: float,
                 eps: float) -> None:
        super().__init__(method_name)

        self.f = f
        self.a = a
        self.b = b
        self.eps = eps

    @property
    def n(self):
        return math.ceil((self.b - self.a) / (self.eps**(0.5)))

    @property
    def h(self):
        return (self.b - self.a) / self.n

    def f_xi(self, i: int):
        return self.f(self.a + i * self.h)

    def compile(self, silent=False):
        if silent:
            blockPrint()

        print_method_introduction(f"{self.method_name}")

        print_header("Initial values")
        print("Bounds", [self.a, self.b])

        result = self.execute_method()

        print("\n")
        print_header("Results")
        print(result)

        if silent:
            enablePrint()

        return result
