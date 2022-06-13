from common.main import InterpolationOrientedMethod, Points


class LeastSquareApproximation(InterpolationOrientedMethod):

    def __init__(self, points: Points, x0: float) -> None:
        super().__init__("Least square approximation", points, x0)

    def execute_method(self, polynomial_degrees: list[int]):
        # ready to use y = a0+a1x+a2x^2 ...
        polynomials = []

        for degree in polynomial_degrees:
