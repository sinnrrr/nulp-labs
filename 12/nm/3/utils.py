from types import Matrix


def matrix_is_square(matrix: Matrix) -> bool:
    row_should_have: int = len(matrix)

    for row in matrix:
        if len(matrix[row]) != row_should_have:
            return False

    return True
