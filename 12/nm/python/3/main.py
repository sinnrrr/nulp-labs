#!/usr/bin/env python3

import textwrap

from colorama import Fore, Style

Row = list[float]
Matrix = list[Row]
Values = list[float]
MethodComputationResult = list[float]


def matrix_is_square(matrix: Matrix) -> bool:
    row_should_have: int = len(matrix)

    for row in matrix:
        if len(row) != row_should_have:
            return False

    return True


def det(m: Matrix, n: int) -> float:
    if n == 1:
        return m[0][0]

    z = 0

    for r in range(n):
        k = m[:]
        del k[r]
        z += m[r][0] * (-1)**r * det([p[1:] for p in k], n - 1)

    return z


def cramers_method(m: Matrix, v: Values) -> MethodComputationResult:
    w = len(v)
    d = det(m, w)

    if d == 0:
        return []

    r = [
        det([r[0:i] + [s] + r[i + 1:] for r, s in zip(m, v)], w) / d
        for i in range(w)
    ]

    return r


def multiply_2d_to_1d_matrices(m2d, m1d) -> MethodComputationResult:
    m2d_length = len(m2d)
    m1d_length = len(m1d)

    if (m2d_length != m1d_length):
        raise ValueError(
            "One of the matrices is not eligible for multiplication")

    width = m1d_length
    result: MethodComputationResult = [0 for _ in range(width)]

    for i in range(m2d_length):
        for j in range(len(m2d[0])):
            # resulted matrix
            result[i] += m2d[i][j] * m1d[j]

    return result


def matrix_method(eq_matrix: Matrix,
                  values: Values) -> MethodComputationResult:
    width = len(values)
    determinant = det(eq_matrix, width)

    if determinant == 0:
        return []

    ac_matrix: Matrix = []

    for row in range(width):
        ac_row = []

        for column in range(width):
            # deep copy without refference
            intermediate = eq_matrix.copy()

            # delete row from matrix
            intermediate.pop(row)

            # delete column from matrix
            intermediate = [
                list(x) for x in zip(*[
                    d for i, d in enumerate(zip(*intermediate)) if i != column
                ])
            ]

            # minor out of intermediate array
            minor = det(intermediate, width - 1)

            # algebraic complement
            ac = pow(-1, row + column) * minor
            ac_row.append(ac)

        ac_matrix.append(ac_row)

    ac_transposed_matrix = [list(x) for x in zip(*ac_matrix)]
    ac_inverted_matrix = [[z / determinant for z in y]
                          for y in ac_transposed_matrix]

    return multiply_2d_to_1d_matrices(ac_inverted_matrix, values)


def run():
    matrix: Matrix = [
        [0.13, -0.14, -2.00],
        [0.75, 0.18, -0.77],
        [0.28, -0.17, 0.39],
    ]

    values: Values = [0.15, 0.11, 0.12]

    if not matrix_is_square(matrix):
        raise ValueError("Please, provide valid square matrix")

    def method_result_description(title: str, result: MethodComputationResult):
        return textwrap.dedent(f"""
        {Fore.CYAN}{title}{Style.RESET_ALL}
        {Fore.RED}Result:{Style.RESET_ALL} {result}
        """)

    output = [("Cramers method", cramers_method(matrix, values)),
              ("Matrix method", matrix_method(matrix, values))]

    for j, k in output:
        print(method_result_description(j, k))


if __name__ == "__main__":
    run()
