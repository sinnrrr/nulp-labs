#!/usr/bin/env python3
from sympy import Pow, lambdify, symbols

x = symbols("x")


def whatever(iterator, x0, eps):
    current_argument = x0

    i = 1
    while True:
        next_argument = iterator(current_argument)

        if abs(next_argument - current_argument) < eps:
            break

        current_argument = next_argument
        i += 1

    return (current_argument, i)


if __name__ == "__main__":
    a_default = str(0)
    b_default = str(4)
    eps_default = str(0.0001)

    a = float(
        input(f"Please, enter point A value (default: {a_default}): ")
        or a_default)
    b = float(
        input(f"Now, enter point B value (default: {b_default}): ")
        or b_default)
    eps = float(
        input(f"Its time for EPS value to roll in (default: {eps_default}): ")
        or eps_default)

    y = Pow(x, 3) - 3 * Pow(x, 2) + 6 * x - 8
    y_prime = y.diff(x)
    y_double_prime = y_prime.diff(x)

    z = (Pow(x, 3) - 3 * Pow(x, 2) - 8) / -6

    f = lambdify(x, y)
    f_prime = lambdify(x, y_prime)
    f_double_prime = lambdify(x, y_double_prime)

    g = lambdify(x, z)

    def newton_iterator(xi):
        return xi - (f(xi) / f_prime(xi))

    def simple_iterator(xi):
        return g(xi)

    def select_boundpoint():
        if f(a) * f_double_prime(a) > 0:
            return a

        if f(b) * f_double_prime(b) > 0:
            return b

        print("Provided boundaries are not appliable")
        quit()

    x0 = select_boundpoint()

    print(f"""
Results

Newtons method: {whatever(newton_iterator, x0, eps)}
Simple itertaions method: {whatever(simple_iterator, x0, eps)}
    """)
