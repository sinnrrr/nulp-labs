#!/usr/bin/env python3

Row = list[int]
Matrix = list[Row]


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


def cramer_method(equation_matrix: Matrix):
    det(equation_matrix)


def run():
    equation_matrix = ask_for_equation_matrix_input()

    cramer_method(equation_matrix)


if __name__ == "__main__":
    run()
