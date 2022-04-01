#!/usr/bin/env python3
from utils import *


def matrix_is_square(matrix: Matrix) -> bool:
    row_should_have: int = len(matrix)

    for row in matrix:
        if len(matrix[row]) != row_should_have:
            return False

    return True


def ask_for_equation_matrix_input():
    equation_matrix: Matrix = []
    rows: int = int(input("Enter the equations count (default - 3): ") or 3)
    columns: int = int(
        input("How many variables will be in each eqation (default - 3): ")
        or 3)

    if not matrix_is_square(equation_matrix):
        raise ValueError("The matrix should be square")

    for i in range(rows):
        equation: Row = []

        for j in range(columns + 1):
            equation.append(
                int(input(f"Enter value for {i + 1} equation of x{j + 1}: ")))

        equation_matrix.append(equation)

    return equation_matrix


def determinant_recursive(A, total=0):
    # Section 1: store indices in list for row referencing
    indices = list(range(len(A)))

    # Section 2: when at 2x2 submatrices recursive calls end
    if len(A) == 2 and len(A[0]) == 2:
        val = A[0][0] * A[1][1] - A[1][0] * A[0][1]
        return val

    # Section 3: define submatrix for focus column and
    #      call this function
    for fc in indices:  # A) for each focus column, ...
        # find the submatrix ...
        As = copy_matrix(A)  # B) make a copy, and ...
        As = As[1:]  # ... C) remove the first row
        height = len(As)  # D)

        for i in range(height):
            # E) for each remaining row of submatrix ...
            #     remove the focus column elements
            As[i] = As[i][0:fc] + As[i][fc + 1:]

        sign = (-1)**(fc % 2)  # F)
        # G) pass submatrix recursively
        sub_det = determinant_recursive(As)
        # H) total all returns from recursion
        total += sign * A[0][fc] * sub_det

    return total


def cramer_method(equation_matrix: Matrix):
    det(equation_matrix)


def run():
    equation_matrix = ask_for_equation_matrix_input()

    cramer_method(equation_matrix)


if __name__ == "__main__":
    run()
