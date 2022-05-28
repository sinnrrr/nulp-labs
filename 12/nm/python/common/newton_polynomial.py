import numpy as np
from common.main import InterpolationOrientedMethod, Points
from common.utils import print_header
from prettytable.prettytable import PrettyTable


# Requirements:
# [-] Step size is constant
# [-] Degree is equal to (<number_of_points> - 1)
class NewtonPolynomialMethod(InterpolationOrientedMethod):

    def __init__(self, points: Points, x0: float) -> None:
        super().__init__("Newton's polynomial", points, x0)

    def newton_coefficient(self):
        """
        x: list or np array contanining x data points
        y: list or np array contanining y data points
        """

        m = len(self.points[0])

        x = np.copy(self.points[0])
        a = np.copy(self.points[1])
        for k in range(1, m):
            a[k:m] = (a[k:m] - a[k - 1]) / (x[k:m] - x[k - 1])

        return a

    # Steps:
    # [-] Calculating f(x_prev, x_curr) and f(x_prev, x_curr, x_next)
    # whereas f(x_prev, x_curr, x_next) equals to ...
    # (f(x_curr, x_next) - f(x_prev, x_curr)) / x_next - x_prev
    # [-] Building the table of values
    # rows: [x_i | f_i | f(x_i, x_ii) | f(x_i, x_ii, x_iii)]
    # [-] Using formula calculating the polynomial
    def execute_method(self):
        """
        x_data: data points at x
        y_data: data points at y
        x: evaluation point(s)
        """
        xp = self.x0
        a = self.newton_coefficient()
        n = len(self.points[0]) - 1  # Degree of polynomial
        yp = a[n]

        print("\n")
        print_header("Iteration process")
        for k in range(1, n + 1):
            yp = a[n - k] + (xp - self.points[0][n - k]) * yp
            print(yp)

        return xp, yp
