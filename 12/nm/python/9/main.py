from common.least_square_approximation import LeastSquareApproximation
from common.main import Points

if __name__ == "__main__":
    points: Points = ([
        4.03,
        4.08,
        4.16,
        4.23,
        4.26,
        4.33,
    ], [2.8, 2.94, 3.2, 3.38, 3.53, 3.75])

    for degree in range(3):
        LeastSquareApproximation(points, degree + 1).compile()
