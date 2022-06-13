from common.lagrange_polynomial import LagrangePolynomialMethod, Points
from common.newton_polynomial import NewtonPolynomialMethod

if __name__ == "__main__":
    points: Points = ([
        0.45, 0.46, 0.47, 0.48, 0.49, 0.50, 0.51, 0.52, 0.53, 0.54
    ], [20.19, 19.61, 18.94, 18.17, 17.30, 16.31, 15.19, 13.94, 12.55, 10.99])
    x0 = 0.455

    for method in [LagrangePolynomialMethod, NewtonPolynomialMethod]:
        method(points, x0).compile()
