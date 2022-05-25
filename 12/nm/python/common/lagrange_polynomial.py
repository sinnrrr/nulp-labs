from common.main import InterpolationOrientedMethod, Points


class LagrangePolynomialMethod(InterpolationOrientedMethod):

    def __init__(self, points: Points, x0: float) -> None:
        super().__init__("Lagrange polynomial", points, x0)

    def execute_method(self):
        x_points = self.points[0]
        y_points = self.points[1]

        n = len(x_points)
        xp = self.x0  # x0 as a starting point
        yp = 0  # interpolated value

        for i in range(n):
            p = 1

            for j in range(n):
                if i == j:
                    continue

                p *= (xp - x_points[j]) / (x_points[i] - x_points[j])

            yp += p * y_points[i]

        return xp, yp
